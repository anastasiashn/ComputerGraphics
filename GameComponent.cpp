#pragma once
#include "GameComponent.h"
#include <d3d11.h>

GameComponent::GameComponent()
{
    game = nullptr;
}

void GameComponent::destroyResources()
{
}

void GameComponent::draw()
{
}

void GameComponent::initialize(Game* game)
{
    this->game = game;
}

void GameComponent::reload()
{
}

void GameComponent::update(float deltaTime, Keyboard keyboard)
{
}

std::vector<CollisionBox*> GameComponent::getCollisionBoxes() {
    return std::vector<CollisionBox*>();
}

std::string GameComponent::getType() {
    return "GameComponent";
}
