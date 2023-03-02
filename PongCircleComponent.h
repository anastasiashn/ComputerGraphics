#pragma once
#include "Game.h"

class PongCircleComponent : public GameComponent
{
public:
    PongCircleComponent();
    virtual void initialize(Game* game) override;
    virtual void draw() override;
    virtual void update(float deltaTime, Keyboard keyboard) override;
    virtual std::string getType() override;

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

    int numberOfTriangles = 10;
    int pixelSize = 20;

    DirectX::XMFLOAT4* points;
    int pointSize;
    int indecesCount;
    float x_offset = 0;
    float y_offset = 0;

    float lastTileCollisionTime = 0;

    DirectX::XMFLOAT2 direction = DirectX::XMFLOAT2(0.0f, 0.0f);
    float speed = 30;
    CollisionBox collisionBox;

    void updatePoints(float deltaTime);
    bool handleCollision(float deltaTime);
    void updateIndeces();
    float toPixelSize(float size, int screenSize, int pixel);
    DirectX::XMFLOAT4 toPixelSize(float x, float y, int pixel);
    void reset(bool directionToTop = true);
};

