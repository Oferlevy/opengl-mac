#include "engine/renderer/VertexBuffer.h"

VertexBuffer::VertexBuffer(size_t size)
{
    glGenBuffers(1, &m_Id);
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

    ASSERT(m_Id, "Failed to create vertex buffer!");
}

VertexBuffer::VertexBuffer(void* data, size_t size)
{
    glGenBuffers(1, &m_Id);
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    ASSERT(m_Id, "Failed to create vertex buffer!");
}

VertexBuffer::VertexBuffer(void* data, size_t size, const BufferLayout& layout)
    : VertexBuffer(data, size)
{
    m_Layout = layout;
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_Id);
}

auto VertexBuffer::Bind() const -> void
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
}

auto VertexBuffer::Unbind() const -> void
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

auto VertexBuffer::SetData(void* data, size_t size) -> void
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

auto VertexBuffer::SetData(void* data, size_t size, size_t offset) -> void
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

auto VertexBuffer::GetLayout() const -> const BufferLayout&
{
    return m_Layout;
}

auto VertexBuffer::SetLayout(const BufferLayout& layout) -> void
{
    m_Layout = layout;
}