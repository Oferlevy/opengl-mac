#include "engine/renderer/IndexBuffer.h"

IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
{
    m_Count = count;

    glGenBuffers(1, &m_Id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    ASSERT(m_Id, "Failed to create index buffer!");
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_Id);
}

auto IndexBuffer::Bind() const -> void
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
}

auto IndexBuffer::Unbind() const -> void
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

auto IndexBuffer::GetCount() const -> uint32_t
{
    return m_Count;
}