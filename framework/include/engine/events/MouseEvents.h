#pragma once

#include "Core.h"
#include "Event.h"

enum class MouseButton : int8_t
{
    None = -1,
    Left = 0,
    Right = 1,
    Middle = 2,
    Button4 = 3,
    Button5 = 4
};

class MouseButtonEvent : public Event
{
public:
    MouseButtonEvent() = default;
    MouseButtonEvent(MouseButton button);

    auto ToString() const -> std::string override;
    auto GetButton() const -> MouseButton;

protected:
    MouseButton m_Button = MouseButton::None;
};

class MousePressedEvent : public MouseButtonEvent
{
public:
    using MouseButtonEvent::MouseButtonEvent;

    EVENT_TYPE(MousePressed)
    EVENT_CATEGORY(MouseButtonEvent)
};

class MouseReleasedEvent : public MouseButtonEvent
{
public:
    using MouseButtonEvent::MouseButtonEvent;

    EVENT_TYPE(MouseReleased)
    EVENT_CATEGORY(MouseButtonEvent)
};

class MouseMovedEvent : public Event
{
public:
    MouseMovedEvent() = default;
    MouseMovedEvent(glm::uvec2 position);

    auto ToString() const->std::string override;

    auto GetX() const -> uint32_t;
    auto GetY() const -> uint32_t;
    auto GetPosition() const -> glm::uvec2;

    EVENT_TYPE(MouseMoved)
    EVENT_CATEGORY(MouseEvent)

private:
    glm::uvec2 m_Position = { 0, 0 };
};

class MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent() = default;
    MouseScrolledEvent(float scroll);

    auto ToString() const -> std::string override;
    auto GetScroll() const -> float;

    EVENT_TYPE(MouseScrolled)
    EVENT_CATEGORY(MouseEvent)

private:
    float m_Scroll = 0.0f;
};