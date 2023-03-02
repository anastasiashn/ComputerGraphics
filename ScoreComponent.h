#pragma once
#include "Game.h"
#include <SpriteBatch.h>
#include <SpriteFont.h>

class ScoreComponent : public GameComponent
{
public:
    ScoreComponent();
    virtual void initialize(Game* game) override;
    virtual void draw() override;
    virtual std::string getType() override;

    void addScore(int first, int second);
    DirectX::DX11::SpriteBatch* spriteBatch;
    DirectX::DX11::SpriteFont* spriteFont;

private:
    int scoreFirst = 0;
    int scoreSecond = 0;
};

