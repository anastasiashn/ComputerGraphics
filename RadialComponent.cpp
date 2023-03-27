#include "RadialComponent.h"
#include "Game.h"

using namespace DirectX;
using namespace SimpleMath;

constexpr int SliceCount = 32;
constexpr int StackCount = 32;

RadialComponent::RadialComponent(const RadialDesc& desc) :
    SphereComponent(desc.Radius, SliceCount, StackCount, desc.PrimaryColor, desc.SecondaryColor),
    spinAxis(desc.SpinAxis), spinSpeed(desc.SpinSpeed), orbitAnchor(desc.OrbitAnchor), orbitRadius(desc.OrbitRadius),
    orbitOrientationForward(desc.OrbitOrientationForward), orbitOrientationUp(desc.OrbitOrientationUp), orbitSpeed(desc.OrbitSpeed)
{
    if (orbitAnchor)
    {
        relativePosition = desc.OrbitOrientationForward * orbitRadius;
        position = orbitAnchor->position + relativePosition;
    }
    else
    {
        position = desc.OrbitOrientationForward * orbitRadius;
    }
}

void RadialComponent::initialize(Game* game)
{
    this->game = game;
    SphereComponent::initialize(game);
}

void RadialComponent::update(float deltaTime)
{
    if (orbitAnchor)
    {
        relativePosition = XMVector4Transform(relativePosition, Matrix::CreateFromAxisAngle(orbitOrientationUp, deltaTime * orbitSpeed));
        position = orbitAnchor->position + relativePosition;
    }
    else
    {
        position = XMVector4Transform(position, Matrix::CreateFromAxisAngle(orbitOrientationUp, deltaTime * orbitSpeed));
    }
    rotation *= Quaternion::CreateFromAxisAngle(spinAxis, spinSpeed * deltaTime);
    SphereComponent::update(deltaTime);
}
