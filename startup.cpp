#include <iostream>
#include "Game.h"
#include "RectangleComponent.h"

int main() {
    RectangleComponent* rectangleComponent = new RectangleComponent();
    std::vector<GameComponent*> gameComponents;
    gameComponents.push_back(rectangleComponent);

    Game game(L"Test game", 800, 800, gameComponents);
    game.run();
}