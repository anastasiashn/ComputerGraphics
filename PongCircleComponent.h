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
    ID3D11Buffer* constantBuffer;

    ID3D11Buffer* indecesBuffer;
    ID3D11Buffer* vertexBuffer;
    UINT* strides;
    UINT* offsets;

    const int numberOfTriangles = 10;
    const int pixelSize = 25;
    const int initialspeed = 1;
    const int speedAfterHit = 2;
    int index = 0;

    DirectX::XMFLOAT4* points;
    int pointSize;
    int indecesCount;
    float x_offset = 0;
    float y_offset = 0;

    float lastTileCollisionTime = 0;

    DirectX::XMFLOAT2 direction = DirectX::XMFLOAT2(0.0f, 0.0f);
    float speed;
    CollisionBox collisionBox;

    void updateCollizionBox();
    void updateConstantBuffer();
    bool handleCollision(float deltaTime);
    void updateIndeces();
    float toPixelSize(float size, int screenSize, int pixel);
    DirectX::XMFLOAT4 toPixelSize(float x, float y, int pixel);
    void reset(bool directionToTop = true);
};

