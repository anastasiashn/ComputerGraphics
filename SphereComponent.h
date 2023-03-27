#pragma once
#include "Game.h"
#include "Simplemath.h"

class SphereComponent : public GameComponent
{
public:
    struct Point
    {
        DirectX::SimpleMath::Vector4 pos;
        DirectX::SimpleMath::Vector4 col;
    };
protected:
    ID3D11InputLayout* layout;
    ID3D11PixelShader* pixelShader;
    ID3DBlob* pixelShaderByteCode;
    ID3D11RasterizerState* rastState;
    ID3D11VertexShader* vertexShader;
    ID3DBlob* vertexShaderByteCode;
    ID3D11Buffer* vertexBuffer;
    ID3D11Buffer* indexBuffer;
    ID3D11Buffer* constBuffer;
    UINT strides[1];
    UINT offsets[1];
    std::vector<Point> points;
    std::vector<int> indices;
public:
    DirectX::SimpleMath::Quaternion rotation;
    DirectX::SimpleMath::Vector3 position;
    SphereComponent(float radius, int sliceCount, int stackCount, DirectX::SimpleMath::Vector4 col1, DirectX::SimpleMath::Vector4 col2);

    void destroyResources() override;
    void draw() override;
    void initialize(Game* game) override;
    void update(float deltaTime) override;
};

