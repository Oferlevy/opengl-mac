#include "engine/events/WindowEvents.h"

WindowResizedEvent::WindowResizedEvent(glm::uvec2 size)
    : m_Size(size) {}

auto WindowResizedEvent::ToString() const -> std::string
{
    auto ss = std::stringstream();
    ss << "WindowResized: " << m_Size.x << ", " << m_Size.y;
    return ss.str();
}

auto WindowResizedEvent::GetWidth() const -> uint32_t
{
    return m_Size.x;
}

auto WindowResizedEvent::GetHeight() const -> uint32_t
{
    return m_Size.y;
}

auto WindowResizedEvent::GetSize() const -> glm::uvec2
{
    return m_Size;
}

auto WindowResizedEvent::GetAspectRatio() const -> float
{
    return static_cast<float>(m_Size.x) / static_cast<float>(m_Size.y);
}