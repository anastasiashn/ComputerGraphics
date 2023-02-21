#pragma once
#include "GameComponent.h"

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

void GameComponent::update(float deltaTime)
{
}
