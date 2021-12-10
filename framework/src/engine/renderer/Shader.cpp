#include "engine/renderer/Shader.h"
#include "engine/utils/File.h"

auto static CompileShader(const std::string& path, uint32_t type) -> uint32_t
{
    auto codeString = File::Read(path);
    auto code = codeString.c_str();

    auto shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);
    
    auto compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled)
    {
        auto maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        auto infoLog = std::vector<char>(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog.data());

        ASSERT(false, "Failed to compile shader: " + path + ":\n" + infoLog.data());
        glDeleteShader(shader);
    }

    return shader;
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
{
    m_Id = glCreateProgram();

    auto vertexShader = CompileShader(vertexPath, GL_VERTEX_SHADER);
    auto fragmentShader = CompileShader(fragmentPath, GL_FRAGMENT_SHADER);
    
    glAttachShader(m_Id, vertexShader);
    glAttachShader(m_Id, fragmentShader);
    glLinkProgram(m_Id);

    auto linked = 0;
    glGetProgramiv(m_Id, GL_LINK_STATUS, &linked);

    if (!linked)
    {
        auto maxLength = 0;
        glGetProgramiv(m_Id, GL_INFO_LOG_LENGTH, &maxLength);

        auto infoLog = std::string(maxLength, ' ');
        glGetProgramInfoLog(m_Id, maxLength, &maxLength, infoLog.data());

        ASSERT(false, "Failed to link program:\n" + infoLog);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    glDetachShader(m_Id, vertexShader);
    glDetachShader(m_Id, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(m_Id);
}

Shader::~Shader()
{
    glDeleteProgram(m_Id);
}

auto Shader::Bind() const -> void
{
    glUseProgram(m_Id);
}

auto Shader::Unbind() const -> void
{
    glUseProgram(0);
}

auto Shader::SetUniform(const std::string& name, bool value) const -> void
{
    glUniform1i(glGetUniformLocation(m_Id, name.c_str()), static_cast<int>(value));
}

auto Shader::SetUniform(const std::string& name, float value) const -> void
{
    glUniform1f(glGetUniformLocation(m_Id, name.c_str()), value);
}

auto Shader::SetUniform(const std::string& name, glm::vec2 value) const -> void
{
    glUniform2fv(glGetUniformLocation(m_Id, name.c_str()), 1, glm::value_ptr(value));
}

auto Shader::SetUniform(const std::string& name, const glm::vec3& value) const -> void
{
    glUniform3fv(glGetUniformLocation(m_Id, name.c_str()), 1, glm::value_ptr(value));
}

auto Shader::SetUniform(const std::string& name, const glm::vec4& value) const -> void
{
    glUniform4fv(glGetUniformLocation(m_Id, name.c_str()), 1, glm::value_ptr(value));
}

auto Shader::SetUniform(const std::string& name, int value) const -> void
{
    glUniform1i(glGetUniformLocation(m_Id, name.c_str()), value);
}

auto Shader::SetUniform(const std::string& name, glm::ivec2 value) const -> void
{
    glUniform2iv(glGetUniformLocation(m_Id, name.c_str()), 1, glm::value_ptr(value));
}

auto Shader::SetUniform(const std::string& name, const glm::ivec3& value) const -> void
{
    glUniform3iv(glGetUniformLocation(m_Id, name.c_str()), 1, glm::value_ptr(value));
}

auto Shader::SetUniform(const std::string& name, const glm::ivec4& value) const -> void
{
    glUniform4iv(glGetUniformLocation(m_Id, name.c_str()), 1, glm::value_ptr(value));
}

auto Shader::SetUniform(const std::string& name, const glm::mat2& value) const -> void
{
    glUniformMatrix2fv(glGetUniformLocation(m_Id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

auto Shader::SetUniform(const std::string& name, const glm::mat3& value) const -> void
{
    glUniformMatrix3fv(glGetUniformLocation(m_Id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

auto Shader::SetUniform(const std::string& name, const glm::mat4& value) const -> void
{
    glUniformMatrix4fv(glGetUniformLocation(m_Id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}