#include "engine/events/KeyboardEvents.h"

KeyEvent::KeyEvent(Key key)
    : m_Key(key) {}

auto KeyEvent::ToString() const->std::string
{
    auto ss = std::stringstream();
    ss << GetName() << ": " << static_cast<char>(m_Key);
    return ss.str();
}

auto KeyEvent::GetKey() const -> Key
{
    return m_Key;
}