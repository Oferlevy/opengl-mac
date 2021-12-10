#pragma once

#include "Core.h"

class IndexBuffer : public CreatableRef<IndexBuffer>
{
public:
    IndexBuffer(uint32_t* indices, uint32_t count);
    ~IndexBuffer();

    // binds the index buffer
    auto Bind() const -> void;

    // unbinds the index buffer
    auto Unbind() const -> void;

    // returns the index count
    auto GetCount() const -> uint32_t;

protected:
    uint32_t m_Count = 0;
    uint32_t m_Id = 0;
};