#pragma once
#include <unordered_set>
#include "Delegates.h"
#include "MouseKeys.h"
#include "DisplayWin32.h"
#include "SimpleMath.h"


class Mouse
{
protected:
	struct RawMouseEventArgs
	{
		int Mode;
		int ButtonFlags;
		int ExtraInformation;
		int Buttons;
		int WheelDelta;
		int X;
		int Y;
	};
	struct InputEventArgs {
		USHORT MakeCode;

		USHORT Flags;

		USHORT VKey;
		UINT   Message;
	};

public:
	struct MouseMoveEventArgs
	{
		DirectX::SimpleMath::Vector2 Position;
		DirectX::SimpleMath::Vector2 Offset;
		int WheelDelta;
	};

	void initialize(DisplayWin32* display);

	DirectX::SimpleMath::Vector2 MousePosition;
	DirectX::SimpleMath::Vector2 MouseOffset;
	int MouseWheelDelta;

	bool IsKeyDown(MouseKeys key);
	void OnMouseMove(RawMouseEventArgs args);
	void OnKeyDown(InputEventArgs args);

private:
	DisplayWin32* display = nullptr;
	std::unordered_set<MouseKeys>* keys;
	void AddPressedKey(MouseKeys key);
	void RemovePressedKey(MouseKeys key);
};

