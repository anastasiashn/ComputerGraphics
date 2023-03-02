#include "CollisionLine.h"
#include "CollisionException.h"

CollisionLine::CollisionLine(DirectX::XMFLOAT2 first, DirectX::XMFLOAT2 second)
{
    this->first = first;
    this->second = second;
}

bool operator>(const CollisionLine& c1, const CollisionLine& c2)
{
    if (CollisionLine::isHorizontal(c1) && CollisionLine::isHorizontal(c2)) {
        return c1.first.y > c2.first.y;
    }

    if (CollisionLine::isVertical(c1) && CollisionLine::isVertical(c2)) {
        return c1.first.x > c2.first.x;
    }

    throw CollisionException();
}

bool operator<(const CollisionLine& c1, const CollisionLine& c2)
{
    if (CollisionLine::isHorizontal(c1) && CollisionLine::isHorizontal(c2)) {
        return c1.first.y < c2.first.y;
    }

    if (CollisionLine::isVertical(c1) && CollisionLine::isVertical(c2)) {
        return c1.first.x < c2.first.x;
    }

    throw CollisionException();
}

bool operator>=(const CollisionLine& c1, const CollisionLine& c2)
{
    if (CollisionLine::isHorizontal(c1) && CollisionLine::isHorizontal(c2)) {
        return c1 > c2 || c1.first.y == c2.first.y;
    }

    if (CollisionLine::isVertical(c1) && CollisionLine::isVertical(c2)) {
        return c1 > c2 || c1.first.x == c2.first.x;
    }

    throw CollisionException();
}

bool operator<=(const CollisionLine& c1, const CollisionLine& c2)
{
    if (CollisionLine::isHorizontal(c1) && CollisionLine::isHorizontal(c2)) {
        return c1 < c2 || c1.first.y == c2.first.y;
    }

    if (CollisionLine::isVertical(c1) && CollisionLine::isVertical(c2)) {
        return c1 < c2 || c1.first.x == c2.first.x;
    }

    throw CollisionException();
}

float operator-(const CollisionLine& c1, const CollisionLine& c2)
{
    if (CollisionLine::isHorizontal(c1) && CollisionLine::isHorizontal(c2)) {
        return c1.first.y - c2.first.y;
    }

    if (CollisionLine::isVertical(c1) && CollisionLine::isVertical(c2)) {
        return c1.first.x - c2.first.x;
    }

    throw CollisionException();
}

float CollisionLine::getMaxX()
{
    return first.x > second.x ? first.x : second.x;
}

float CollisionLine::getMinX()
{
    return first.x < second.x ? first.x : second.x;
}

float CollisionLine::getMaxY()
{
    return first.y > second.y ? first.y : second.y;
}

float CollisionLine::getMinY()
{
    return first.y < second.y ? first.y : second.y;
}

bool CollisionLine::isHorizontal(const CollisionLine& line)
{
    return line.first.y == line.second.y;
}

bool CollisionLine::isVertical(const CollisionLine& line)
{
    return line.first.x == line.second.x;
}
