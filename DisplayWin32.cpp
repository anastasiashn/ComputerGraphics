#include <iostream>

#include "WindowContainer.h"

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// All other messages
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;

	default:
	{
		// retrieve ptr to window class
		WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		// forward message to window class handler
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
}

LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
		if (pWindow == nullptr) //Sanity check
		{
			exit(-1);
		}

		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void DisplayWin32::initialize(WindowContainer* windowContainer, LPCWSTR applicationName, int clientWidth, int clientHeight)
{
	this->applicationName = applicationName;
	this->clientWidth = clientWidth;
	this->clientHeight = clientHeight;
	this->hInstance = GetModuleHandle(nullptr);

	initializeWc();

	RECT windowRect = { 0, 0, static_cast<LONG>(clientWidth), static_cast<LONG>(clientHeight) };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	auto dwStyle = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME;

	auto posX = (GetSystemMetrics(SM_CXSCREEN) - clientWidth) / 2;
	auto posY = (GetSystemMetrics(SM_CYSCREEN) - clientHeight) / 2;

	this->hWnd = CreateWindowEx(WS_EX_APPWINDOW, applicationName, applicationName,
		dwStyle,
		posX, posY,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr, nullptr, hInstance, windowContainer);

	ShowWindow(this->hWnd, SW_SHOW);
	SetForegroundWindow(this->hWnd);
	SetFocus(this->hWnd);

	ShowCursor(true);
}

void DisplayWin32::initializeWc() {
	this->wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	this->wc.lpfnWndProc = HandleMessageSetup;
	this->wc.cbClsExtra = 0;
	this->wc.cbWndExtra = 0;
	this->wc.hInstance = hInstance;
	this->wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	this->wc.hIconSm = this->wc.hIcon;
	this->wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	this->wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	this->wc.lpszMenuName = nullptr;
	this->wc.lpszClassName = applicationName;
	this->wc.cbSize = sizeof(WNDCLASSEX);
	RegisterClassEx(&this->wc);
}

