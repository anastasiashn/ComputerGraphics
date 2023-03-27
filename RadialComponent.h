#pragma once
#include "SphereComponent.h"

class RadialComponent;

struct RadialDesc
{
    float Radius;
    float SpinSpeed;
    DirectX::SimpleMath::Vector3 SpinAxis;
    RadialComponent* OrbitAnchor;
    DirectX::SimpleMath::Vector3 OrbitOrientationForward;
    DirectX::SimpleMath::Vector3 OrbitOrientationUp;
    float OrbitRadius;
    float OrbitSpeed;
    DirectX::SimpleMath::Vector4 PrimaryColor;
    DirectX::SimpleMath::Vector4 SecondaryColor;
    RadialDesc() : Radius(1.0f), SpinSpeed(1.0f), SpinAxis(DirectX::SimpleMath::Vector3::Up),
        OrbitAnchor(nullptr), OrbitOrientationForward(DirectX::SimpleMath::Vector3::Forward),
        OrbitOrientationUp(DirectX::SimpleMath::Vector3::Up),
        OrbitRadius(0.0f), OrbitSpeed(0.0f), PrimaryColor(DirectX::SimpleMath::Vector4::One),
        SecondaryColor(DirectX::SimpleMath::Vector4::Zero) {}
};

class RadialComponent : public SphereComponent
{
protected:
    float spinSpeed;
    DirectX::SimpleMath::Vector3 spinAxis;
    RadialComponent* orbitAnchor;
    DirectX::SimpleMath::Vector3 orbitOrientationForward;
    DirectX::SimpleMath::Vector3 orbitOrientationUp;
    float orbitRadius;
    float orbitSpeed;
    DirectX::SimpleMath::Vector3 relativePosition;
public:
    RadialComponent(const RadialDesc& desc);
    void initialize(Game* game) override;
    void update(float deltaTime) override;
};
