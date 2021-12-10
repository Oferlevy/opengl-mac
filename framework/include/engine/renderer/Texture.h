#pragma once

#include "Core.h"

class Texture : public CreatableRef<Texture>
{
public:
    Texture(const std::string& path);
    ~Texture();
    
    // binds the texture
    auto Bind() const -> void;
    
    // unbinds the texture
    auto Unbind() const -> void;

private:
    uint32_t m_Id = 0;
};