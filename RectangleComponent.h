#pragma once
#include "Game.h"

class RectangleComponent : public GameComponent
{
public:
    RectangleComponent();
    virtual void initialize(Game* game) override;
    virtual void draw() override;

private:
    ID3D11InputLayout* layout;
    ID3D11PixelShader* pixelShader;
    ID3DBlob* pixelShaderByteCode;
    ID3D11VertexShader* vertexShader;
    ID3DBlob* vertexShaderByteCode;

    ID3D11Buffer* indecesBuffer;
    ID3D11Buffer* vertexBuffer;
    UINT* strides;
    UINT* offsets;
};

