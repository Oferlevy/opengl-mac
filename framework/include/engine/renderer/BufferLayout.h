#pragma once

#include "Core.h"

enum class ShaderDataType : uint8_t
{
    None,
    Int,
    Int2,
    Int3,
    Int4,
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4
};

struct BufferLayoutElement
{
    std::string name = "";
    ShaderDataType type = ShaderDataType::None;
    uint16_t size = 0;
    uint16_t offset = 0;
    uint8_t componentsCount = 0;
    bool normalized = false;

    BufferLayoutElement() = default;
    BufferLayoutElement(const std::string& name, ShaderDataType type, bool normalized = false);
};

class BufferLayout
{
public:
    BufferLayout() = default;
    BufferLayout(const std::initializer_list<BufferLayoutElement>& elements);

    // returns the stride
    auto GetStride() const -> uint16_t;

    // returns a vector of BufferLayoutElement
    auto GetElements() const -> const std::vector<BufferLayoutElement>&;

    auto begin() const -> std::vector<BufferLayoutElement>::const_iterator; // iterators for looping over a BufferLayout object
    auto end() const -> std::vector<BufferLayoutElement>::const_iterator;

private:
    std::vector<BufferLayoutElement> m_Elements;
    uint16_t m_Stride = 0;
};