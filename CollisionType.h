#pragma once
#include <string>

enum class CollisionType {
    top,
    bottom,
    left,
    right,
    none,
    windowLeft,
    widowRight,
    windowTop,
    windowBottom
};

class CollisionTypeHelper {
public:
    static bool isWindow(CollisionType collisionType) {
        return collisionType == CollisionType::windowLeft
            || collisionType == CollisionType::widowRight
            || collisionType == CollisionType::windowTop
            || collisionType == CollisionType::windowBottom;
    }

    static std::string toString(CollisionType collisionType) {
        switch (collisionType)
        {
        case CollisionType::top:
            return "top";
        case CollisionType::bottom:
            return "bottom";
        case CollisionType::left:
            return "left";
        case CollisionType::right:
            return "right";
        case CollisionType::none:
            return "none";
        case CollisionType::windowLeft:
            return "windowLeft";
        case CollisionType::widowRight:
            return "widowRight";
        case CollisionType::windowTop:
            return "windowTop";
        case CollisionType::windowBottom:
            return "windowBottom";
        default:
            return "default";
        }
    }
};