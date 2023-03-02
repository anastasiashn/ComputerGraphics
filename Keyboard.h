#pragma once
#include "KeyboardEvent.h"
#include <queue>

class Keyboard
{
public:
    Keyboard();
    bool KeyIsPressed(unsigned char keycode) const;
    bool KeyBufferIsEmpty();
    bool CharBufferIsEmpty();
    KeyboardEvent ReadKey();
    unsigned char ReadChar();
    void OnKeyPressed(unsigned char keycode);
    void OnKeyReleased(unsigned char keycode);
    void OnChar(char character) noexcept;
    bool IsKeysAutoRepeat();
    bool IsCharsAutoRepeat();
private:
    bool autoRepeatKeys = false;
    bool autoRepeatChars = false;
    bool keyStates[256];
    std::queue<KeyboardEvent> keyBuffer;
    std::queue<unsigned char> charBuffer;
};

