#pragma once
#include <iostream>

class CollisionException : public std::exception {
public:
    char* what() {
        return (char*)"CollisionException";
    }
};