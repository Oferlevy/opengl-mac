#pragma once

#include "Core.h"
#include "BufferLayout.h"

class VertexBuffer : public CreatableRef<VertexBuffer>
{
public:
    VertexBuffer(size_t size);
    VertexBuffer(void* data, size_t size);
    VertexBuffer(void* data, size_t size, const BufferLayout& layout);
    ~VertexBuffer();

    // binds the vertex buffer
    auto Bind() const -> void;

    // unbinds the vertex buffer
    auto Unbind() const -> void;

    // sets the data of the buffer on the gpu
    auto SetData(void* data, size_t size) -> void;

    // sets the data of the buffer on the gpu
    auto SetData(void* data, size_t size, size_t offset) -> void;

    // sets the layout
    auto SetLayout(const BufferLayout& layout) -> void;

    // returns the layout
    auto GetLayout() const -> const BufferLayout&;

protected:
    BufferLayout m_Layout;
    
    uint32_t m_Id = 0;
};