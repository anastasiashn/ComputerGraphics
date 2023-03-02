#pragma once
#include "DisplayWin32.h"
#include "Keyboard.h"

class WindowContainer
{
public:
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
	Keyboard keyboard;
	DisplayWin32 display;
private:

};

