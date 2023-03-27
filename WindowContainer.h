#pragma once
#include "DisplayWin32.h"
#include "Keyboard.h"
#include "Mouse.h"

class WindowContainer
{
public:
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
	DisplayWin32 display;
	Keyboard keyboard;
	Mouse mouse;
private:

};

