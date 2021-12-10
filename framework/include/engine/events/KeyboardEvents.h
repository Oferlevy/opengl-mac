#pragma once

#include "Core.h"
#include "Event.h"

// not all keys are defined yet
enum class Key : uint16_t
{
    None = 0,
    Space = 32,
    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 98,
    Y = 89,
    Z = 90,
    Escape = 256,
    Enter = 257,
    Tab = 258,
    Backspace = 259,
    Insert = 260,
    Delete = 261,
    RightArrow = 262,
    LeftArrow = 263,
    DownArrow = 264,
    UpArrow = 265,
    PageUp = 266,
    PageDown = 267,
    Home = 268,
    End = 269,
    CapsLock = 280,
    ScollLock = 281,
    NumLock = 282,
    PrintScreen = 283,
    Pause = 284,
    F1 = 290,
    F2 = 291,
    F3 = 292,
    F4 = 293,
    F5 = 294,
    F6 = 295,
    F7 = 296,
    F8 = 297,
    F9 = 298,
    F10 = 299,
    F11 = 300,
    F12 = 301,
    F13 = 302,
    F14 = 303,
    F15 = 304,
    F16 = 305,
    F17 = 306,
    F18 = 307,
    F19 = 308,
    F20 = 309,
    F21 = 310,
    F22 = 311,
    F23 = 312,
    F24 = 313,
    F25 = 314,
    LeftControl = 341
};

class KeyEvent : public Event
{
public:
    KeyEvent() = default;
    KeyEvent(Key key);

    auto ToString() const -> std::string override;
    auto GetKey() const -> Key;

protected:
    Key m_Key = Key::None;
};

class KeyPressedEvent : public KeyEvent
{
public:
    using KeyEvent::KeyEvent;

    EVENT_TYPE(KeyPressed)
    EVENT_CATEGORY(KeyboardEvent)
};

class KeyTypedEvent : public KeyEvent
{
public:
    using KeyEvent::KeyEvent;

    EVENT_TYPE(KeyTyped)
    EVENT_CATEGORY(KeyboardEvent)
};

class KeyReleasedEvent : public KeyEvent
{
public:
    using KeyEvent::KeyEvent;

    EVENT_TYPE(KeyReleased)
    EVENT_CATEGORY(KeyboardEvent)
};