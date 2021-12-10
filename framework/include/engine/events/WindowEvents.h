#pragma once

#include "Core.h"
#include "Event.h"

class WindowResizedEvent : public Event
{
public:
    WindowResizedEvent() = default;
    WindowResizedEvent(glm::uvec2 size);

    auto ToString() const -> std::string override;

    auto GetWidth() const -> uint32_t;
    auto GetHeight() const -> uint32_t;
    auto GetSize() const -> glm::uvec2;
    auto GetAspectRatio() const -> float;

    EVENT_TYPE(WindowResized)
    EVENT_CATEGORY(WindowEvent)

private:
    glm::uvec2 m_Size = { 0, 0 };
};

class WindowMaximizedEvent : public Event
{
public:
    EVENT_TYPE(WindowMaximized)
    EVENT_CATEGORY(WindowEvent)
};

class WindowGainedFocusEvent : public Event
{
public:
    EVENT_TYPE(WindowGainedFocus)
    EVENT_CATEGORY(WindowEvent)
};

class WindowLostFocusEvent : public Event
{
public:
    EVENT_TYPE(WindowLostFocus)
    EVENT_CATEGORY(WindowEvent)
};

class WindowClosedEvent : public Event
{
public:
    EVENT_TYPE(WindowClosed)
    EVENT_CATEGORY(WindowEvent)
};