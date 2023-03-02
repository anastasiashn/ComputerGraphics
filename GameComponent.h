#pragma once
#include "CollisionBox.h"
#include "Keyboard.h"
#include <directxmath.h>
#include <vector>

class Game;

class GameComponent
{
protected:
    Game* game = nullptr;
    float toPixelSize(float size, int screenSize, int pixel);
    DirectX::XMFLOAT4 toPixelSize(float x, float y, int pixel);
public:
    GameComponent();
    virtual void destroyResources();
    virtual void draw();
    virtual void initialize(Game* game);
    virtual void reload();
    virtual void update(float deltaTime, Keyboard keyboard);
    virtual std::vector<CollisionBox*> getCollisionBoxes();
    virtual std::string getType();
};

