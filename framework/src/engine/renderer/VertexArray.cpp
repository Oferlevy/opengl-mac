#include "engine/renderer/VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_Id);
    ASSERT(m_Id, "Failed to create vertex array!");
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_Id);
}

auto VertexArray::Bind() const -> void
{
    glBindVertexArray(m_Id);
}

auto VertexArray::Unbind() const -> void
{
    glBindVertexArray(0);
}

auto VertexArray::SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) -> void
{
    glBindVertexArray(m_Id);
    vertexBuffer->Bind();

    auto& layout = vertexBuffer->GetLayout();
    for (const auto& element : vertexBuffer->GetLayout())
    {
        switch (element.type)
        {
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
            {
                glVertexAttribIPointer(
                    m_VertexBufferIndex,
                    element.componentsCount,
                    GL_INT,
                    layout.GetStride(),
                    reinterpret_cast<const void*>(element.offset)
                );
                
                glEnableVertexAttribArray(m_VertexBufferIndex);
                m_VertexBufferIndex++;
                break;
            }
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            {
                glVertexAttribPointer(
                    m_VertexBufferIndex,
                    element.componentsCount,
                    GL_FLOAT,
                    element.normalized ? GL_TRUE : GL_FALSE,
                    layout.GetStride(),
                    reinterpret_cast<const void*>(element.offset)
                );

                glEnableVertexAttribArray(m_VertexBufferIndex);
                m_VertexBufferIndex++;
                break;
            }
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:
            {
                for (auto i = 0u; i < element.componentsCount; i++)
                {
                    glVertexAttribPointer(
                        m_VertexBufferIndex,
                        element.componentsCount,
                        GL_FLOAT,
                        element.normalized ? GL_TRUE : GL_FALSE,
                        layout.GetStride(),
                        reinterpret_cast<const void*>(element.offset + i * static_cast<uint64_t>(element.componentsCount) * sizeof(float))
                    );
                    glEnableVertexAttribArray(m_VertexBufferIndex);
                    glVertexAttribDivisor(m_VertexBufferIndex, 1);
                    m_VertexBufferIndex++;
                }
                break;
            }
            default:
                ASSERT(false, "Unknown data type!");
        }
    }

    m_VertexBuffer = vertexBuffer;
}

auto VertexArray::GetVertexBuffer() -> const Ref<VertexBuffer>&
{
    return m_VertexBuffer;
}

auto VertexArray::GetIndexBuffer() -> const Ref<IndexBuffer>&
{
    return m_IndexBuffer;
}

auto VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) -> void
{
    glBindVertexArray(m_Id);
    indexBuffer->Bind();

    m_IndexBuffer = indexBuffer;
}