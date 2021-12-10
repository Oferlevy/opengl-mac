#pragma once

#include "Core.h"

enum class EventType : uint8_t
{
    None = 0,

    WindowResized,
    WindowMaximized,
    WindowGainedFocus,
    WindowLostFocus,
    WindowMoved,
    WindowClosed,

    KeyPressed,
    KeyTyped,
    KeyReleased,

    MousePressed,
    MouseReleased,
    MouseMoved,
    MouseScrolled
};

enum class EventCategory : uint8_t
{
    None             = 0,
    WindowEvent      = 1 << 0,
    KeyboardEvent    = 1 << 1,
    MouseEvent       = 1 << 2,
    MouseButtonEvent = 1 << 3
};

#define EVENT_TYPE(type) auto static inline GetStaticType() -> EventType { return EventType::type; } \
                         auto inline GetType() const -> EventType override { return GetStaticType(); } \
                         auto inline GetName() const -> std::string override { return #type; }

#define EVENT_CATEGORY(category) auto inline GetCategory() const -> EventCategory override { return EventCategory::category; }

class Event
{
public:
    friend class EventDispatcher;
    friend class Application;

public:
    auto virtual GetType() const -> EventType = 0;
    auto virtual GetCategory() const -> EventCategory = 0;
    auto virtual GetName() const -> std::string = 0;
    auto virtual ToString() const -> std::string;

    auto InCategory(EventCategory category) -> bool;

private:
    bool m_Handled = false;
};

class EventDispatcher
{
public:
    EventDispatcher(const Event& e);

    template <class T, class Func>
    auto Dispatch(const Func& func) -> bool
    {
        if (m_Event.GetType() == T::GetStaticType())
        {
            m_Event.m_Handled = func(static_cast<T&>(m_Event));
            return true;
        }

        return false;
    }

private:
    Event& m_Event;
};

auto inline operator << (std::ostream& os, const Event& e) -> std::ostream&
{
    return os << e.ToString();
}