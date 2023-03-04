#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include "PongTileComponent.h"
#include "ConstantBuffer.h"

PongTileComponent::PongTileComponent(bool isUpTile) 
	: collisionBox()
{
	this->isUpTile = isUpTile;
	this->topCollisionType = isUpTile ? CollisionType::bottom : CollisionType::top;

	GameComponent::GameComponent();
	y_offset = isUpTile ? 0.9 : -0.9;
	left_button = isUpTile ? VK_LEFT : 'A';
	right_button = isUpTile ? VK_RIGHT : 'D';
}

void PongTileComponent::initialize(Game* game)
{
	GameComponent::initialize(game);

	ID3DBlob* errorVertexCode = nullptr;
	auto res = D3DCompileFromFile(L"./Shaders/VertexShader.hlsl",
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
			MessageBox(game->getDisplay().hWnd, L"VertexShader.hlsl", L"Missing Shader File", MB_OK);
		}

		return;
	}

	D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 1.0f, 0.0f, 1.0f)", nullptr, nullptr };

	ID3DBlob* errorPixelCode;
	res = D3DCompileFromFile(
		L"./Shaders/PixelShader.hlsl",
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

	pointSize = 8;
	points = new DirectX::XMFLOAT4[pointSize]{
		DirectX::XMFLOAT4(tileHalfWidth,	tileHalfHeight, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(-tileHalfWidth,	-tileHalfHeight, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(tileHalfWidth,	-tileHalfHeight, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::XMFLOAT4(-tileHalfWidth,	tileHalfHeight, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	};

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

	updateCollizionBox();
}

void PongTileComponent::draw()
{
	game->context->IASetInputLayout(layout);
	game->context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	game->context->IASetIndexBuffer(indecesBuffer, DXGI_FORMAT_R32_UINT, 0);
	game->context->IASetVertexBuffers(0, 1, &vertexBuffer, strides, offsets);
	game->context->VSSetConstantBuffers(0u, 1u, &constantBuffer);
	game->context->VSSetShader(vertexShader, nullptr, 0);
	game->context->PSSetShader(pixelShader, nullptr, 0);

	game->context->DrawIndexed(indecesCount, 0, 0);
}

void PongTileComponent::update(float deltaTime, Keyboard keyboard)
{
	updateXOffset(deltaTime, keyboard);
	updateCollizionBox();
	updateConstantBuffer();
}

void PongTileComponent::updateXOffset(float deltaTime, Keyboard keyboard) 
{
	if (keyboard.KeyIsPressed(left_button) && keyboard.KeyIsPressed(right_button)) {
		return;
	}
	auto windowCollision = checkWindowCollision();
	if (keyboard.KeyIsPressed(left_button) && windowCollision != CollisionType::windowLeft) {
		x_offset -= deltaTime * speed;
	}

	if (keyboard.KeyIsPressed(right_button) && windowCollision != CollisionType::widowRight) {
		x_offset += deltaTime * speed;
	}
}

CollisionType PongTileComponent::checkWindowCollision() {
	for (auto& componentBox : getCollisionBoxes())
	{
		auto collision = game->checkWindowCollision(componentBox);
		if (collision != CollisionType::none) {
			return collision;
		}
	}

	return CollisionType::none;
}


void PongTileComponent::updateCollizionBox()
{
	collisionBox.bottomLeftPoint = DirectX::XMFLOAT2(x_offset - tileHalfWidth, y_offset - tileHalfHeight);
	collisionBox.width = tileHalfWidth * 2;
	collisionBox.height = tileHalfHeight * 2;
}

void PongTileComponent::updateConstantBuffer() {
	const ConstantBuffer cb =
	{
		{
			DirectX::XMMatrixTranspose(
				DirectX::XMMatrixTranslation(x_offset, y_offset, 0)
			)
		}
	};

	CD3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;
	game->device->CreateBuffer(&cbd, &csd, &constantBuffer);
}

void PongTileComponent::updateIndeces() {
	int indeces[] = { 0,1,2, 1,0,3 };
	indecesCount = std::size(indeces);

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

float PongTileComponent::toPixelSize(float size, int screenSize, int pixel)
{
	return size * pixel / screenSize;
}

DirectX::XMFLOAT4 PongTileComponent::toPixelSize(float x, float y, int pixel)
{
	return DirectX::XMFLOAT4(toPixelSize(x, game->getDisplay().clientWidth, pixel), toPixelSize(y, game->getDisplay().clientHeight, pixel), 1.0f, 1.0f);
}

std::vector<CollisionBox*> PongTileComponent::getCollisionBoxes()
{
	auto result = std::vector<CollisionBox*>();
	result.push_back(&collisionBox);
	return result;
}

std::string PongTileComponent::getType()
{
	return "PongTileComponent";
}

CollisionBox PongTileComponent::getCollisionBox()
{
	return collisionBox;
}
