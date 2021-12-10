#include "engine/events/Event.h"

EventDispatcher::EventDispatcher(const Event& e)
    : m_Event(const_cast<Event&>(e)) {}

auto Event::ToString() const -> std::string
{
    return GetName();
}

auto inline Event::InCategory(EventCategory category) -> bool
{
    return static_cast<uint8_t>(GetCategory()) & static_cast<uint8_t>(category);
}