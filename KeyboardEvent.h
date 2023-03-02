#pragma once
#include "KeyboardEventType.h"

class KeyboardEvent
{
private:
	KeyboardEventType type;
	unsigned char code;
public:
	KeyboardEvent();
	KeyboardEvent(KeyboardEventType type, unsigned char code);
	bool IsPress() const;
	bool IsRelease() const;
	unsigned char GetCode() const;
};