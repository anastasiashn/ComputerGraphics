#include "Keyboard.h"

Keyboard::Keyboard()
{
    for (int i = 0; i < 256; ++i)
        this->keyStates[i] = false;
}

bool Keyboard::KeyIsPressed(unsigned char keycode) const
{
    return this->keyStates[keycode];
}

bool Keyboard::KeyBufferIsEmpty()
{
    return this->keyBuffer.empty();
}

bool Keyboard::CharBufferIsEmpty()
{
    return this->charBuffer.empty();
}

KeyboardEvent Keyboard::ReadKey()
{
    if (this->keyBuffer.empty()) {
        return KeyboardEvent();
    }

    KeyboardEvent e = this->keyBuffer.front();
    this->keyBuffer.pop();
    return e;
}

unsigned char Keyboard::ReadChar()
{
    if (this->charBuffer.empty()) {
        return 0u;
    }

    unsigned char e = this->charBuffer.front();
    this->keyBuffer.pop();
    return e;
}

void Keyboard::OnKeyPressed(unsigned char keycode)
{
    this->keyStates[keycode] = true;
    this->keyBuffer.push(KeyboardEvent(KeyboardEventType::Press, keycode));
}

void Keyboard::OnKeyReleased(unsigned char keycode)
{
    this->keyStates[keycode] = false;
    this->keyBuffer.push(KeyboardEvent(KeyboardEventType::Release, keycode));
}

void Keyboard::OnChar(char character) noexcept
{
    this->charBuffer.push(character);
}

bool Keyboard::IsKeysAutoRepeat()
{
    return this->autoRepeatKeys;
}

bool Keyboard::IsCharsAutoRepeat()
{
    return this->autoRepeatChars;
}
