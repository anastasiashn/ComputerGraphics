#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include "PongCircleComponent.h"
#include "PongTileComponent.h"
#include "ScoreComponent.h"

float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

float RandomNumber(int min, int max) {
	return rand() % (max - min) + min;
}

bool RandomBool() {
	return RandomNumber(0, 100) <= 50;
}


PongCircleComponent::PongCircleComponent() : collisionBox()
{
	GameComponent::GameComponent();
	collisionBox.bottomLeftPoint = DirectX::XMFLOAT2(0, 0);
	collisionBox.width = 0;
	collisionBox.height = 0;
}

void PongCircleComponent::initialize(Game* game)
{
	GameComponent::initialize(game);

	ID3DBlob* errorVertexCode = nullptr;
	auto res = D3DCompileFromFile(L"./Shaders/MyVeryFirstShader.hlsl",
		nullptr /*macros*/,
		nullptr /*include*/,
		"VSMain",
		"vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&vertexShaderByteCode,
		&errorVertexCode);

	if (FAILED(res)) {
		// If the shader failed to compile it should have written something to the error message.
		if (errorVertexCode) {
			char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(game->getDisplay().hWnd, L"MyVeryFirstShader.hlsl", L"Missing Shader File", MB_OK);
		}

		return;
	}

	D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 1.0f, 0.0f, 1.0f)", nullptr, nullptr };

	ID3DBlob* errorPixelCode;
	res = D3DCompileFromFile(
		L"./Shaders/MyVeryFirstShader.hlsl",
		Shader_Macros /*macros*/,
		nullptr /*include*/,
		"PSMain",
		"ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&pixelShaderByteCode,
		&errorPixelCode);

	game->device->CreateVertexShader(
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		nullptr, &vertexShader);

	game->device->CreatePixelShader(
		pixelShaderByteCode->GetBufferPointer(),
		pixelShaderByteCode->GetBufferSize(),
		nullptr, &pixelShader);

	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
		D3D11_INPUT_ELEMENT_DESC {
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0},
		D3D11_INPUT_ELEMENT_DESC {
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0}
	};

	game->device->CreateInputLayout(
		inputElements,
		2,
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		&layout);

	strides = new UINT{ sizeof(DirectX::XMFLOAT4) * 2 };
	offsets = new UINT{ 0 };

	updatePoints(0);
	reset(RandomBool());
}

void PongCircleComponent::draw()
{
	game->context->IASetInputLayout(layout);
	game->context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	game->context->IASetIndexBuffer(indecesBuffer, DXGI_FORMAT_R32_UINT, 0);
	game->context->IASetVertexBuffers(0, 1, &vertexBuffer, strides, offsets);
	game->context->VSSetShader(vertexShader, nullptr, 0);
	game->context->PSSetShader(pixelShader, nullptr, 0);

	game->context->DrawIndexed(indecesCount, 0, 0);
}

void PongCircleComponent::update(float deltaTime, Keyboard keyboard)
{
	updatePoints(deltaTime);
	handleCollision(deltaTime);

	D3D11_BUFFER_DESC vertexBufDesc = {};
	vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufDesc.CPUAccessFlags = 0;
	vertexBufDesc.MiscFlags = 0;
	vertexBufDesc.StructureByteStride = 0;
	vertexBufDesc.ByteWidth = sizeof(DirectX::XMFLOAT4) * pointSize;

	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = points;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	game->device->CreateBuffer(&vertexBufDesc, &vertexData, &vertexBuffer);

	updateIndeces();
}

void PongCircleComponent::updatePoints(float deltaTime) 
{
	x_offset += direction.x * deltaTime * speed;
	y_offset += direction.y * deltaTime * speed;

	pointSize = (numberOfTriangles + 1) * 2;
	points = (DirectX::XMFLOAT4*)malloc(sizeof(DirectX::XMFLOAT4) * pointSize);

	points[0] = toPixelSize(0.0f + x_offset, 0.0f + y_offset, pixelSize);
	points[1] = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	float deltaTheta = 2 * M_PI / numberOfTriangles;
	for (int i = 0; i < numberOfTriangles; i++) {
		float theta = i * deltaTheta;
		int index = i * 2 + 2;

		points[index] = toPixelSize(cos(theta) + x_offset, sin(theta) + y_offset, pixelSize);
		points[index + 1] = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	auto radius = points[2].x - points[0].x;
	collisionBox.bottomLeftPoint.x = points[0].x - radius;
	collisionBox.bottomLeftPoint.y = points[0].y - radius;
	collisionBox.width = radius * 2;
	collisionBox.height = radius * 2;
}

bool PongCircleComponent::handleCollision(float deltaTime) {
	auto windowCollision = game->checkWindowCollision(&collisionBox);
	if (windowCollision == CollisionType::windowLeft || windowCollision == CollisionType::widowRight) {
		direction.x *= -1;
		return true;
	}
	if (windowCollision == CollisionType::windowTop || windowCollision == CollisionType::windowBottom) {
		auto isBottomWin = windowCollision == CollisionType::windowTop;
		auto scoreComponents = this->game->getComponentsByType("ScoreComponent");
		if (!scoreComponents.empty()) {
			for (auto& component : scoreComponents) {
				ScoreComponent* scoreComponent = dynamic_cast<ScoreComponent*>(component);
				if (isBottomWin) {
					scoreComponent->addScore(1, 0);
				}
				else {
					scoreComponent->addScore(0, 1);
				}
			}
		}
		reset(isBottomWin);
		return true;
	}
	
	lastTileCollisionTime = lastTileCollisionTime - deltaTime >= 0 ? lastTileCollisionTime - deltaTime : 0;
	if (lastTileCollisionTime > 0) {
		return false;
	}

	auto tileComponents = this->game->getComponentsByType("PongTileComponent");
	if (tileComponents.empty()) {
		return false;
	}

	for (auto& component : tileComponents)
	{
		PongTileComponent* tileComponent = dynamic_cast<PongTileComponent*>(component);
		auto tileCollisionBox = tileComponent->getCollisionBox();
		auto tileCollisionType = tileCollisionBox.checkCollision(&collisionBox);
		// if (tileCollisionType != CollisionType::none) {
		if (tileCollisionType == tileComponent->topCollisionType) {
			direction.y *= -1;
			auto tileCenterX = tileCollisionBox.bottomLeftPoint.x + tileCollisionBox.width / 2;
			auto circleCenterX = collisionBox.bottomLeftPoint.x + collisionBox.width / 2;
			auto delta = tileCenterX - circleCenterX;
			direction.x = -delta * 4;
			lastTileCollisionTime = 0.2f;
			speed = 80;
			return true;
		}
	}

	return false;
}

void PongCircleComponent::updateIndeces() {
	indecesCount = numberOfTriangles * 3;
	int* indeces = (int*)malloc(sizeof(int) * indecesCount);
	for (int i = 0; i < numberOfTriangles; ++i) {
		int index = i * 3;
		indeces[index] = 0;
		indeces[index + 1] = i + 1;
		indeces[index + 2] = (i + 2) - ((i + 2) / (numberOfTriangles + 1)) * numberOfTriangles;
	}

	D3D11_BUFFER_DESC indexBufDesc = {};
	indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufDesc.CPUAccessFlags = 0;
	indexBufDesc.MiscFlags = 0;
	indexBufDesc.StructureByteStride = 0;
	indexBufDesc.ByteWidth = sizeof(int) * indecesCount;

	D3D11_SUBRESOURCE_DATA indexData = {};
	indexData.pSysMem = indeces;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	game->device->CreateBuffer(&indexBufDesc, &indexData, &indecesBuffer);
}

float PongCircleComponent::toPixelSize(float size, int screenSize, int pixel)
{
	return size * pixel / screenSize;
}

DirectX::XMFLOAT4 PongCircleComponent::toPixelSize(float x, float y, int pixel)
{
	return DirectX::XMFLOAT4(toPixelSize(x, game->getDisplay().clientWidth, pixel), toPixelSize(y, game->getDisplay().clientHeight, pixel), 1.0f, 1.0f);
}

std::string PongCircleComponent::getType()
{
	return "PongCircleComponent";
}

void PongCircleComponent::reset(bool directionToTop) {
	x_offset = 0;
	y_offset = 0;
	speed = 20;
	auto xDirection = RandomNumber(30, 80) / 100.0f;
	auto yDirection = RandomNumber(30, 80) / 100.0f;
	auto xNegative = RandomBool() ? -1 : 1;
	xDirection *= xNegative;
	direction = DirectX::XMFLOAT2(xDirection, directionToTop ? yDirection : -yDirection);
	lastTileCollisionTime = 0;
}