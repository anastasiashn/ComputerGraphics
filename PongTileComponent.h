#pragma once
#include "Game.h"

class PongTileComponent : public GameComponent
{
public:
    bool isUpTile = false;

    PongTileComponent(bool isUpTile);
    virtual void initialize(Game* game) override;
    virtual void draw() override;
    virtual void update(float deltaTime, Keyboard keyboard) override;
    virtual std::vector<CollisionBox*> getCollisionBoxes() override;
    virtual std::string getType() override;
    CollisionBox getCollisionBox();

    CollisionType topCollisionType;

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
    int pixelSize = 25;

    DirectX::XMFLOAT4* points;
    int pointSize;
    int indecesCount;
    float x_offset = 0;
    float y_offset = 0;
    unsigned char left_button;
    unsigned char right_button;

    float speed = 2;
    CollisionBox collisionBox;

    void updatePoints(float deltaTime);
    void updateXOffset(float deltaTime, Keyboard keyboard);
    void updateIndeces();
    float toPixelSize(float size, int screenSize, int pixel);
    DirectX::XMFLOAT4 toPixelSize(float x, float y, int pixel);
    CollisionType checkWindowCollision();
};

