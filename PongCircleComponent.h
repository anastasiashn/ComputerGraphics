#pragma once
#include "Game.h"

class PongCircleComponent : public GameComponent
{
public:
    PongCircleComponent(bool temporary_circle = false);
    virtual void initialize(Game* game) override;
    virtual void draw() override;
    virtual void update(float deltaTime, Keyboard keyboard) override;
    virtual std::string getType() override;
    virtual void destroyResources() override;
    void setCircleData(
        float x_offset,
        float y_offset,
        float speed,
        DirectX::XMFLOAT2 direction);

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

    bool temporary_circle = false;

    const int numberOfTriangles = 10;
    const int pixelSize = 25;
    const int initialspeed = 1;
    const int speedAfterHit = 2;
    const float disableCollisionTime = 0.05f;
    int index = 0;

    DirectX::XMFLOAT4* points;
    int pointSize;
    int indecesCount;
    float x_offset = 0;
    float y_offset = 0;

    float lastTileCollisionTime = 0;
    float lastVerticalWindowCollisionTime = 0;

    DirectX::XMFLOAT2 direction = DirectX::XMFLOAT2(0.0f, 0.0f);
    float speed;
    CollisionBox collisionBox;

    void updatePoints(DirectX::XMFLOAT4 color);
    void updateCollizionBox();
    void updateConstantBuffer();
    bool handleCollision(float deltaTime);
    bool handleVerticalWindowCollision(float deltaTime);
    bool handleHorizontalWindowCollision(float deltaTime);
    bool handleTileCollision(float deltaTime);
    void updateIndeces();
    float toPixelSize(float size, int screenSize, int pixel);
    DirectX::XMFLOAT4 toPixelSize(float x, float y, int pixel);
    void reset(bool directionToTop = true);
    void addNewCircle();
};

