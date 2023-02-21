#pragma once

class Game;

class GameComponent
{
protected:
    Game* game;
public:
    GameComponent();
    virtual void destroyResources();
    virtual void draw();
    virtual void initialize(Game* game);
    virtual void reload();
    virtual void update(float deltaTime);
};

