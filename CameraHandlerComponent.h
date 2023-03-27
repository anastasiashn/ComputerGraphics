#pragma once
#include "Game.h"
#include "Mouse.h"

class CameraHandlerComponent : public GameComponent
{
public:
    DirectX::SimpleMath::Vector3 up;
    DirectX::SimpleMath::Vector3 relativePos;
    Game* game;
    float yaw;
    float pitch;
    float speed;
    void initialize(Game* g) override;
    void update(float deltaTime) override;
};

