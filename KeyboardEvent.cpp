#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent()
	:
	type(KeyboardEventType::Invalid),
	code(0u) { }

KeyboardEvent::KeyboardEvent(KeyboardEventType type, unsigned char code)
	:
	type(type),
	code(code) { }

bool KeyboardEvent::IsPress() const {
	return type == KeyboardEventType::Press;
}

bool KeyboardEvent::IsRelease() const {
	return type == KeyboardEventType::Release;
}

unsigned char KeyboardEvent::GetCode() const
{
	return code;
}