#pragma once

#include "Core.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArray : public CreatableRef<VertexArray>
{
public:
    VertexArray();
    ~VertexArray();

    // binds the vertex buffer
    auto Bind() const -> void;

    // unbinds the vertex buffer
    auto Unbind() const -> void;

    // sets the vertex buffer
    auto SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) -> void;

    // sets the index buffer
    auto SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) -> void;

    // returns the vertex buffers
    auto GetVertexBuffer() -> const Ref<VertexBuffer>&;

    // returns the index buffer
    auto GetIndexBuffer() -> const Ref<IndexBuffer>&;

protected:
    Ref<VertexBuffer> m_VertexBuffer;
    Ref<IndexBuffer> m_IndexBuffer;
    
    uint8_t m_VertexBufferIndex = 0;
    uint32_t m_Id = 0;
};