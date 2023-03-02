#include <iostream>
#include "Game.h"
#include "PongCircleComponent.h"
#include "PongTileComponent.h"
#include "ScoreComponent.h"

int main() {
    srand((unsigned)time(NULL));
    std::vector<GameComponent*> gameComponents;
    gameComponents.push_back(new PongCircleComponent());
    gameComponents.push_back(new PongTileComponent(true));
    gameComponents.push_back(new PongTileComponent(false));
    gameComponents.push_back(new ScoreComponent());

    Game game;
    game.initialize(L"Test game", 500, 500, gameComponents);
    game.run();
}