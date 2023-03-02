#pragma once
#include "CollisionLine.h"
#include "CollisionType.h"
#include <directxmath.h>

class CollisionBox
{
public:
    DirectX::XMFLOAT2 bottomLeftPoint;
    float width;
    float height;

    static CollisionBox fromPoints(DirectX::XMFLOAT4* points, int pointsCount);
    CollisionBox();

    DirectX::XMFLOAT2 getBottomRight();
    DirectX::XMFLOAT2 getTopLeft();
    DirectX::XMFLOAT2 getTopRight();
    CollisionLine getTop();
    CollisionLine getBottom();
    CollisionLine getLeft();
    CollisionLine getRight();

    CollisionBox toPixels(int screenWidth, int screenHeight);
    CollisionType checkCollision(CollisionBox* to);
private:
    bool checkTopCollision(CollisionBox* to);
    bool checkRightCollision(CollisionBox* to);
    bool checkNoneCollision(CollisionBox* to);
    bool checkLeftCollision(CollisionBox* to);
    bool checkBottomCollision(CollisionBox* to);
};

