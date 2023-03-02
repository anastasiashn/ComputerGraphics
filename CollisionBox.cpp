#include <stdlib.h>
#include <iostream>
#include "CollisionBox.h"

CollisionBox::CollisionBox()
{
   bottomLeftPoint = DirectX::XMFLOAT2(0, 0);
   width = 0;
   height = 0;
}

CollisionBox CollisionBox::fromPoints(DirectX::XMFLOAT4* points, int pointsCount) {
    float minX = 1.0f;
    float maxX = -1.0f;
    float minY = 1.0f;
    float maxY = -1.0f;
    for (int index = 0; index < pointsCount; ++index) {
        float x = points[index].x;
        float y = points[index].y;
        if (minX > x) {
            minX = x;
        }
        if (maxX < x) {
            maxX = x;
        }
        if (minY > y) {
            minY = y;
        }
        if (maxY < y) {
            maxY = y;
        }
    }
    CollisionBox collisionBox;
    collisionBox.bottomLeftPoint = DirectX::XMFLOAT2(minX, minY);
    collisionBox.width = maxX - minX;
    collisionBox.height = maxY - minY;

    return collisionBox;
}

DirectX::XMFLOAT2 CollisionBox::getBottomRight()
{
    return DirectX::XMFLOAT2(bottomLeftPoint.x + width, bottomLeftPoint.y);
}

DirectX::XMFLOAT2 CollisionBox::getTopLeft()
{
    return DirectX::XMFLOAT2(bottomLeftPoint.x, bottomLeftPoint.y + height);
}

DirectX::XMFLOAT2 CollisionBox::getTopRight()
{
    return DirectX::XMFLOAT2(bottomLeftPoint.x + width, bottomLeftPoint.y + height);
}

CollisionLine CollisionBox::getTop()
{
    return CollisionLine(getTopLeft(), getTopRight());
}

CollisionLine CollisionBox::getBottom()
{
    return CollisionLine(bottomLeftPoint, getBottomRight());
}

CollisionLine CollisionBox::getLeft()
{
    return CollisionLine(bottomLeftPoint, getTopLeft());
}

CollisionLine CollisionBox::getRight()
{
    return CollisionLine(getBottomRight(), getTopRight());
}

CollisionBox CollisionBox::toPixels(int screenWidth, int screenHeight) {
    CollisionBox result;
    result.bottomLeftPoint = DirectX::XMFLOAT2(bottomLeftPoint.x * screenWidth, bottomLeftPoint.y * screenHeight);
    result.width = width * screenWidth;
    result.height = height * screenHeight;
    return result;
}

CollisionType CollisionBox::checkCollision(CollisionBox* to) {
    if (checkNoneCollision(to)) {
        return CollisionType::none;
    }

    if (checkTopCollision(to)) {
        return CollisionType::top;
    }

    if (checkRightCollision(to)) {
        return CollisionType::right;
    }

    if (checkLeftCollision(to)) {
        return CollisionType::left;
    }

    if (checkBottomCollision(to)) {
        return CollisionType::bottom;
    }

    return CollisionType::none;
}

bool CollisionBox::checkTopCollision(CollisionBox* to) {
    if (getTop() > to->getTop()) {
        return false;
    }

    if (getLeft() >= to->getLeft() && getRight() <= to->getRight()) {
        return true;
    }

    if (getLeft() <= to->getLeft() && getRight() >= to->getRight()) {
        return true;
    }

    if (getRight() >= to->getLeft() && getRight() < to->getRight()) {
        float thisTopHigherToBottom = getTop() - to->getBottom();
        float thisRightToLeft = getRight() - to->getLeft();
        return abs(thisTopHigherToBottom) < abs(thisRightToLeft);
    }

    if (getLeft() <= to->getRight() && getLeft() > to->getLeft()) {
        float thisTopHigherToBottom = getTop() - to->getBottom();
        float toRightThisLeft = getLeft() - to->getRight();
        return abs(thisTopHigherToBottom) < abs(toRightThisLeft);
    }

    return false;
}

bool CollisionBox::checkRightCollision(CollisionBox* to) {
    if (getRight() > to->getRight()) {
        return false;
    }

    if (getTop() >= to->getTop() && getBottom() <= to->getBottom()) {
        return true;
    }

    if (getTop() <= to->getTop() && getBottom() >= to->getBottom()) {
        return true;
    }

    if (getRight() >= to->getLeft() && getRight() < to->getRight() && getTop() < to->getTop()) {
        float thisTopHigherToBottom = getTop() - to->getBottom();
        float thisRightToLeft = getRight() - to->getLeft();
        return abs(thisTopHigherToBottom) > abs(thisRightToLeft);
    }

    if (getRight() >= to->getLeft() && getRight() < to->getRight() && getTop() > to->getTop()) {
        float thisBottomHigherToTop = getBottom() - to->getTop();
        float thisRightToLeft = getRight() - to->getLeft();
        return abs(thisBottomHigherToTop) > abs(thisRightToLeft);
    }

    return false;
}

bool CollisionBox::checkLeftCollision(CollisionBox* to) {
    if (getLeft() < to->getLeft()) {
        return false;
    }

    if (getTop() >= to->getTop() && getBottom() <= to->getBottom()) {
        return true;
    }

    if (getTop() <= to->getTop() && getBottom() >= to->getBottom()) {
        return true;
    }

    if (getLeft() <= to->getRight() && getLeft() > to->getLeft() && getTop() < to->getTop()) {
        float thisTopHigherToBottom = getTop() - to->getBottom();
        float thisLeftToRight = getLeft() - to->getRight();
        return abs(thisTopHigherToBottom) > abs(thisLeftToRight);
    }

    if (getLeft() <= to->getRight() && getLeft() > to->getLeft() && getTop() > to->getTop()) {
        float thisBottomHigherToTop = getBottom() - to->getTop();
        float thisLeftToRight = getLeft() - to->getRight();
        return abs(thisBottomHigherToTop) > abs(thisLeftToRight);
    }

    return false;
}

bool CollisionBox::checkBottomCollision(CollisionBox* to) {
    if (getBottom() < to->getBottom()) {
        return false;
    }

    if (getLeft() >= to->getLeft() && getRight() <= to->getRight()) {
        return true;
    }

    if (getLeft() <= to->getLeft() && getRight() >= to->getRight()) {
        return true;
    }

    if (getRight() >= to->getLeft() && getRight() < to->getRight()) {
        float thisBottomHigherToTop = getBottom() - to->getTop();
        float thisRightToLeft = getRight() - to->getLeft();
        return abs(thisBottomHigherToTop) < abs(thisRightToLeft);
    }

    if (getLeft() <= to->getRight() && getLeft() > to->getLeft()) {
        float thisBottomHigherToTop = getBottom() - to->getTop();
        float toRightThisLeft = getLeft() - to->getRight();
        return abs(thisBottomHigherToTop) < abs(toRightThisLeft);
    }

    return false;
}

bool CollisionBox::checkNoneCollision(CollisionBox* to) {
    return getTop() < to->getBottom()
        || getRight() < to->getLeft()
        || getBottom() > to->getTop()
        || getLeft() > to->getRight();
}