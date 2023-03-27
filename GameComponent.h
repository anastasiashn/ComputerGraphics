#pragma once
#include "Keyboard.h"
#include <directxmath.h>
#include <vector>
#include <string>
using namespace DirectX;

class Game;

class GameComponent
{
protected:
    Game* game = nullptr;
    float toPixelSize(float size, int screenSize, int pixel);
    XMFLOAT4 toPixelSize(float x, float y, int pixel);
    bool is_initialised = false;
public:
    GameComponent();
    virtual void destroyResources();
    virtual void draw();
    virtual void initialize(Game* game);
    virtual void reload();
    virtual void update(float deltaTime);
    virtual std::string getType();
};

