#include <iostream>
#include "ScoreComponent.h"

ScoreComponent::ScoreComponent()
{
    GameComponent::GameComponent();
}

void ScoreComponent::initialize(Game* game)
{
    if (this->is_initialised) {
        return;
    }

    GameComponent::initialize(game);
    spriteBatch = new DirectX::DX11::SpriteBatch(this->game->context);
    spriteFont = new DirectX::DX11::SpriteFont(this->game->device.Get(), L"Data\\Fonts\\comic_sand_ms_16.spritefont");
}

void ScoreComponent::draw()
{
    std::string scoreFirstString = std::to_string(scoreFirst);
    std::string scoreSecondString = std::to_string(scoreSecond);
    spriteBatch->Begin();
    spriteFont->DrawString(
        spriteBatch,
        std::wstring(scoreSecondString.begin(), scoreSecondString.end()).c_str(),
        DirectX::XMFLOAT2(0, this->game->getDisplay().clientHeight / 2 - 16),
        DirectX::Colors::White,
        0.0f,
        DirectX::XMFLOAT2(0, 0),
        DirectX::XMFLOAT2(1.0f, 1.0f));
    spriteFont->DrawString(
        spriteBatch,
        std::wstring(scoreFirstString.begin(), scoreFirstString.end()).c_str(),
        DirectX::XMFLOAT2(0, this->game->getDisplay().clientHeight / 2 + 16),
        DirectX::Colors::White,
        0.0f,
        DirectX::XMFLOAT2(0, 0),
        DirectX::XMFLOAT2(1.0f, 1.0f));
    spriteBatch->End();
}

std::string ScoreComponent::getType()
{
    return "ScoreComponent";
}

void ScoreComponent::addScore(int first, int second)
{
    this->scoreFirst += first;
    this->scoreSecond += second;
}
