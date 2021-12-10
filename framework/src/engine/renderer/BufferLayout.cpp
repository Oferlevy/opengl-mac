#include "engine/renderer/BufferLayout.h"

/* //////////////////////////////////
//////// BufferLayoutElement ////////
////////////////////////////////// */

auto static GetSize(ShaderDataType type) -> uint16_t
{
    switch (type)
    {
        case ShaderDataType::Float:  return 4;
        case ShaderDataType::Float2: return 8;
        case ShaderDataType::Float3: return 12;
        case ShaderDataType::Float4: return 16;
        case ShaderDataType::Int:    return 4;
        case ShaderDataType::Int2:   return 8;
        case ShaderDataType::Int3:   return 12;
        case ShaderDataType::Int4:   return 16;
        case ShaderDataType::Mat3:   return 36;
        case ShaderDataType::Mat4:   return 64;
        default: ASSERT(false, "Unknown data type!");
    }
}

auto static GetComponentsCount(ShaderDataType type) -> uint8_t
{
    switch (type)
    {
        case ShaderDataType::Float:  return 1;
        case ShaderDataType::Float2: return 2;
        case ShaderDataType::Float3: return 3;
        case ShaderDataType::Float4: return 4;
        case ShaderDataType::Int:    return 1;
        case ShaderDataType::Int2:   return 2;
        case ShaderDataType::Int3:   return 3;
        case ShaderDataType::Int4:   return 4;
        case ShaderDataType::Mat3:   return 9;
        case ShaderDataType::Mat4:   return 16;
        default: ASSERT(false, "Unknown data type!");
    }
}

BufferLayoutElement::BufferLayoutElement(const std::string& name, ShaderDataType type, bool normalized)
    : name(name), type(type), size(GetSize(type)), componentsCount(GetComponentsCount(type)), normalized(normalized) {}

/* ///////////////////////////
//////// BufferLayout ////////
/////////////////////////// */
 
BufferLayout::BufferLayout(const std::initializer_list<BufferLayoutElement>& elements)
    : m_Elements(elements)
{
    for (auto& element : m_Elements)
    {
        element.offset = m_Stride;
        m_Stride += element.size;
    }
}

auto BufferLayout::GetStride() const -> uint16_t
{
    return m_Stride;
}

auto BufferLayout::GetElements() const -> const std::vector<BufferLayoutElement>&
{
    return m_Elements;
}

auto BufferLayout::begin() const -> std::vector<BufferLayoutElement>::const_iterator
{
    return m_Elements.begin();
}

auto BufferLayout::end() const -> std::vector<BufferLayoutElement>::const_iterator
{
    return m_Elements.end();
}