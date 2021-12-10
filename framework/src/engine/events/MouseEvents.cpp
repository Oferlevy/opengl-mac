#include "engine/events/MouseEvents.h"

MouseButtonEvent::MouseButtonEvent(MouseButton button)
    : m_Button(button) {}

auto MouseButtonEvent::ToString() const -> std::string
{
    auto ss = std::stringstream();
    ss << GetName() << ": " << static_cast<int>(m_Button);
    return ss.str();
}

auto MouseButtonEvent::GetButton() const -> MouseButton
{
    return m_Button;
}

MouseMovedEvent::MouseMovedEvent(glm::uvec2 position)
    : m_Position(position) {}

auto MouseMovedEvent::ToString() const -> std::string
{
    auto ss = std::stringstream();
    ss << GetName() << ": " << m_Position.x << ", " << m_Position.y;
    return ss.str();
}

auto MouseMovedEvent::GetX() const -> uint32_t
{
    return m_Position.x;
}

auto MouseMovedEvent::GetY() const -> uint32_t
{
    return m_Position.y;
}

auto MouseMovedEvent::GetPosition() const -> glm::uvec2
{
    return m_Position;
}

MouseScrolledEvent::MouseScrolledEvent(float scroll)
    : m_Scroll(scroll) {}

auto MouseScrolledEvent::ToString() const->std::string
{
    auto ss = std::stringstream();
    ss << GetName() << ": " << m_Scroll;
    return ss.str();
}

auto MouseScrolledEvent::GetScroll() const -> float
{
    return m_Scroll;
}