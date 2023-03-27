#include "CameraHandlerComponent.h"

void CameraHandlerComponent::initialize(Game* game) {
    this->game = game;
    this->speed = 0.2f;
}

void CameraHandlerComponent::update(float deltaTime)
{
    if (game->getMouse().IsKeyDown(MouseKeys::LeftButton)) {
        yaw -= 0.004f * game->getMouse().MouseOffset.x;
        while (yaw < -XM_2PI)
            yaw += XM_2PI;
        while (yaw < XM_2PI)
            yaw += XM_2PI;
        pitch -= 0.004f * game->getMouse().MouseOffset.y;
        game->camera->Up = XMVector4Transform(DirectX::SimpleMath::Vector3::Up, DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(yaw, pitch, 0.0f));
        game->camera->Target = game->camera->Position;
        game->camera->Target += XMVector4Transform(DirectX::SimpleMath::Vector3::Forward, DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(yaw, pitch, 0.0f));
    }

    if (game->getKeyboard().KeyIsPressed('W'))
    {
        DirectX::SimpleMath::Vector3 tmp = XMVector4Transform(
            DirectX::SimpleMath::Vector3::Forward,
            DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(yaw, pitch, 0.0f));
        tmp.Normalize();
        game->camera->Position += speed * tmp;
    }
    if (game->getKeyboard().KeyIsPressed('S'))
    {
        DirectX::SimpleMath::Vector3 tmp = XMVector4Transform(DirectX::SimpleMath::Vector3::Backward,
            DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(yaw, pitch, 0.0f));
        tmp.Normalize();
        game->camera->Position += speed * tmp;
    }
    if (game->getKeyboard().KeyIsPressed('A'))
    {
        DirectX::SimpleMath::Vector3 tmp = XMVector4Transform(DirectX::SimpleMath::Vector3::Left,
            DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(yaw, pitch, 0.0f));
        tmp.Normalize();
        game->camera->Position += speed * tmp;
    }
    if (game->getKeyboard().KeyIsPressed('D'))
    {
        DirectX::SimpleMath::Vector3 tmp = XMVector4Transform(
            DirectX::SimpleMath::Vector3::Right,
            DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(yaw, pitch, 0.0f));
        tmp.Normalize();
        game->camera->Position += speed * tmp;
    }
    if (game->getKeyboard().KeyIsPressed('E'))
    {
        game->camera->Position += speed * DirectX::SimpleMath::Vector3::Up;
    }
    if (game->getKeyboard().KeyIsPressed('Z'))
    {
        game->camera->Position += speed * DirectX::SimpleMath::Vector3::Down;
    }
    game->camera->Up = XMVector4Transform(
        DirectX::SimpleMath::Vector3::Up,
        DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(yaw, pitch, 0.0f));
    game->camera->Target = game->camera->Position;
    game->camera->Target += XMVector4Transform(DirectX::SimpleMath::Vector3::Forward,
        DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(yaw, pitch, 0.0f));
}

