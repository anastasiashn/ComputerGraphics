#include "Mouse.h"
#include "MouseButton.h"

void Mouse::OnKeyDown(InputEventArgs args)
{
	bool Break = args.Flags & 0x01;

	auto key = static_cast<MouseKeys>(args.VKey);

	if (Break) {
		if (keys->count(key)) RemovePressedKey(key);
	}
	else {
		if (!keys->count(key)) AddPressedKey(key);
	}
}

void Mouse::OnMouseMove(RawMouseEventArgs args)
{
	if (args.ButtonFlags & static_cast<int>(MouseButtonFlags::LeftButtonDown))
		AddPressedKey(MouseKeys::LeftButton);
	if (args.ButtonFlags & static_cast<int>(MouseButtonFlags::LeftButtonUp))
		RemovePressedKey(MouseKeys::LeftButton);
	if (args.ButtonFlags & static_cast<int>(MouseButtonFlags::RightButtonDown))
		AddPressedKey(MouseKeys::RightButton);
	if (args.ButtonFlags & static_cast<int>(MouseButtonFlags::RightButtonUp))
		RemovePressedKey(MouseKeys::RightButton);
	if (args.ButtonFlags & static_cast<int>(MouseButtonFlags::MiddleButtonDown))
		AddPressedKey(MouseKeys::MiddleButton);
	if (args.ButtonFlags & static_cast<int>(MouseButtonFlags::MiddleButtonUp))
		RemovePressedKey(MouseKeys::MiddleButton);

	POINT p;
	GetCursorPos(&p);
	ScreenToClient(display->hWnd, &p);

	MousePosition = DirectX::SimpleMath::Vector2(p.x, p.y);
	MouseOffset = DirectX::SimpleMath::Vector2(args.X, args.Y);
	MouseWheelDelta = args.WheelDelta;
}

void Mouse::AddPressedKey(MouseKeys key)
{
	keys->insert(key);
}

void Mouse::RemovePressedKey(MouseKeys key)
{
	keys->erase(key);
}

void Mouse::initialize(DisplayWin32* display)
{
	this->display = display;
	this->keys = new std::unordered_set<MouseKeys>();
}

bool Mouse::IsKeyDown(MouseKeys key)
{
	return keys->count(key);
}
