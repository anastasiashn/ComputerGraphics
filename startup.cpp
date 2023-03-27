#include <iostream>
#include "Game.h"
#include "CameraHandlerComponent.h"
#include "RadialComponent.h"

using namespace DirectX;
using namespace SimpleMath;

int main() {
    srand((unsigned)time(NULL));
    std::vector<GameComponent*> gameComponents;

    CameraHandlerComponent cameraHandler;
    gameComponents.push_back(&cameraHandler);

	RadialDesc sunDesc = {};
	sunDesc.SpinSpeed = 1.0f;
	sunDesc.Radius = 3.0f;
	sunDesc.PrimaryColor = Vector4(236.f / 255.f, 1.f, 134.f / 255.f, 1.f);
	sunDesc.SecondaryColor = Vector4(153.f / 255.f, 76.f / 255.f, 0.f, 1.f);
	RadialComponent sun(sunDesc);
	gameComponents.push_back(&sun);

	RadialDesc mercuryDesc = {};
	mercuryDesc.SpinSpeed = 1.0f;
	mercuryDesc.Radius = 0.7f;
	mercuryDesc.OrbitAnchor = &sun;
	mercuryDesc.OrbitRadius = 4.0f;
	mercuryDesc.OrbitSpeed = 2.0f;
	mercuryDesc.OrbitOrientationForward = XMVector4Transform(mercuryDesc.OrbitOrientationForward, Matrix::CreateFromAxisAngle(Vector3::Right, 7.0f * XM_PI / 180.0f));
	mercuryDesc.OrbitOrientationUp = XMVector4Transform(mercuryDesc.OrbitOrientationUp, Matrix::CreateFromAxisAngle(Vector3::Right, 7.0f * XM_PI / 180.0f));
	RadialComponent mercury(mercuryDesc);
	gameComponents.push_back(&mercury);

	RadialDesc venusDesc = {};
	venusDesc.SpinSpeed = -0.8f;
	venusDesc.Radius = 1.0f;
	venusDesc.OrbitAnchor = &sun;
	venusDesc.OrbitRadius = 7.0f;
	venusDesc.OrbitSpeed = 1.0f;
	venusDesc.OrbitOrientationForward = XMVector4Transform(mercuryDesc.OrbitOrientationForward, Matrix::CreateFromAxisAngle(Vector3::Right, 3.0f * XM_PI / 180.0f));
	venusDesc.OrbitOrientationUp = XMVector4Transform(mercuryDesc.OrbitOrientationUp, Matrix::CreateFromAxisAngle(Vector3::Right, 3.0f * XM_PI / 180.0f));
	venusDesc.PrimaryColor = Vector4(51.f / 255.f, 25.f / 255.f, 0.0f / 255.f, 1.f);
	venusDesc.SecondaryColor = Vector4(153.f / 255.f, 76.f / 255.f, 0.0f / 255.f, 1.f);
	RadialComponent venus(venusDesc);
	gameComponents.push_back(&venus);

	RadialDesc earthDesc = {};
	earthDesc.SpinSpeed = 0.8f;
	earthDesc.Radius = 1.0f;
	earthDesc.OrbitAnchor = &sun;
	earthDesc.OrbitRadius = 10.0f;
	earthDesc.OrbitSpeed = 0.8f;
	earthDesc.PrimaryColor = Vector4(0.0f, 0.0f, 0.5f, 1.0f);
	earthDesc.SecondaryColor = Vector4(0.0f, 0.7f, 0.0f, 1.0f);
	RadialComponent earth(earthDesc);
	gameComponents.push_back(&earth);

	RadialDesc moonDesc = {};
	moonDesc.SpinSpeed = 0.8f;
	moonDesc.Radius = 0.3f;
	moonDesc.OrbitAnchor = &earth;
	moonDesc.OrbitRadius = 2.0f;
	moonDesc.OrbitSpeed = 1.8f;
	RadialComponent moon(moonDesc);
	gameComponents.push_back(&moon);

	RadialDesc newDesc = {};
	newDesc.SpinSpeed = 0.8f;
	newDesc.Radius = 0.3f;
	newDesc.OrbitAnchor = &venus;
	newDesc.OrbitRadius = 2.0f;
	newDesc.OrbitSpeed = 1.8f;
	newDesc.PrimaryColor = Vector4(0.7f, 0.0f, 0.0f, 1.0f);
	newDesc.SecondaryColor = Vector4(0.7f, 0.0f, 0.0f, 1.0f);
	RadialComponent newsphere(newDesc);
	gameComponents.push_back(&newsphere);


    Game game;
    game.initialize(L"Test game", 800, 800, gameComponents);
    game.run();
}