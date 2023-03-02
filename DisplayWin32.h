#pragma once
#include "Keyboard.h"
#include <Windows.h>

class WindowContainer;

class DisplayWin32
{
public:
    int clientHeight;
    int clientWidth;
    HINSTANCE hInstance;
    HWND hWnd;
    HMODULE module;
    WNDCLASSEX wc;
    LPCWSTR applicationName;

    void initialize(WindowContainer* windowContainer, LPCWSTR applicationName, int clientWidth, int clientHeight);
private:
    void initializeWc();
};

