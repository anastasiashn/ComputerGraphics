#pragma once
#include <directxmath.h>

class CollisionLine
{
public:
    DirectX::XMFLOAT2 first;
    DirectX::XMFLOAT2 second;
    CollisionLine(DirectX::XMFLOAT2 first, DirectX::XMFLOAT2 second);
    friend bool operator> (const CollisionLine& c1, const CollisionLine& c2);
    friend bool operator< (const CollisionLine& c1, const CollisionLine& c2);
    friend bool operator>= (const CollisionLine& c1, const CollisionLine& c2);
    friend bool operator<= (const CollisionLine& c1, const CollisionLine& c2);
    friend float operator- (const CollisionLine& c1, const CollisionLine& c2);
    float getMaxX();
    float getMinX();
    float getMaxY();
    float getMinY();
private:
    static bool isHorizontal(const CollisionLine& line);
    static bool isVertical(const CollisionLine& line);
};

