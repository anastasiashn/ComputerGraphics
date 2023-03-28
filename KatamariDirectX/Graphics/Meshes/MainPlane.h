#pragma once
#include "..\\Vertex.h"
#include "..\\VertexBuffer.h"
#include "..\\IndexBuffer.h"
#include "..\\ConstantBuffer.h"


using namespace DirectX;

class MainPlane
{
public:
	bool Initialize(
		ID3D11Device* device,
		ID3D11DeviceContext* deviceContext
	);

	void SetTexture(ID3D11ShaderResourceView* texture);
	void Draw(
		ConstantBuffer<CB_VS_VertexShader>& cb_vs_vertexshader, 
		const DirectX::SimpleMath::Matrix& viewProjectionMatrix
	);
	void Draw(ConstantBuffer<CB_VS_Mesh_Transform>& cb_vs_vertexshader);

private:

	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;
	ID3D11ShaderResourceView* texture = nullptr;

	VertexBuffer<Vertex> vertexBuffer;
	IndexBuffer indexBuffer;

	DirectX::SimpleMath::Matrix worldMatrix = XMMatrixIdentity();
};