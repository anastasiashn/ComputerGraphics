#pragma once
#include <windows.h>

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

    DisplayWin32(LPCWSTR applicationName, int clientWidth, int clientHeight);
private:
    void initializeWc();
};

