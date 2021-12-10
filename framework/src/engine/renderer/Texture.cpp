#include "engine/renderer/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

Texture::Texture(const std::string& path)
{
    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(1);
    
    int width, height, channels;
    auto data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    
    ASSERT(data, "Failed to load texture: " + path);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_Id);
}

auto Texture::Bind() const -> void
{
    glBindTexture(GL_TEXTURE_2D, m_Id);
}

auto Texture::Unbind() const -> void
{
    glBindTexture(GL_TEXTURE_2D, 0);
}