#include <iostream>
#include "Game.h"
#include "RectangleComponent.h"

int main() {
    RectangleComponent* rectangleComponent = new RectangleComponent(0,0);
    RectangleComponent* rectangleComponent2 = new RectangleComponent(0.1,0.1);
    std::vector<GameComponent*> gameComponents;
    gameComponents.push_back(rectangleComponent);
    gameComponents.push_back(rectangleComponent2);

    Game game(L"Test game", 800, 800, gameComponents);
    game.run();
}