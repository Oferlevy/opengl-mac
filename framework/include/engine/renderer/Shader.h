#pragma once

#include "Core.h"

class Shader : public CreatableRef<Shader>
{
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath = "");
    ~Shader();

    // binds the shader
    auto Bind() const -> void;

    // unbinds the shader
    auto Unbind() const -> void;

    // sets a uniform bool
    auto SetUniform(const std::string& name, bool value) const -> void;

    // sets a uniform float
    auto SetUniform(const std::string& name, float value) const -> void;

    // sets a uniform float2
    auto SetUniform(const std::string& name, glm::vec2 value) const -> void;

    // sets a uniform float3
    auto SetUniform(const std::string& name, const glm::vec3& value) const -> void;

    // sets a uniform float4
    auto SetUniform(const std::string& name, const glm::vec4& value) const -> void;

    // sets a uniform int
    auto SetUniform(const std::string& name, int value) const -> void;

    // sets a uniform int2
    auto SetUniform(const std::string& name, glm::ivec2 value) const -> void;

    // sets a uniform int3
    auto SetUniform(const std::string& name, const glm::ivec3& value) const -> void;

    // sets a uniform int4
    auto SetUniform(const std::string& name, const glm::ivec4& value) const -> void;

    // sets a uniform mat2
    auto SetUniform(const std::string& name, const glm::mat2& value) const -> void;

    // sets a uniform mat3
    auto SetUniform(const std::string& name, const glm::mat3& value) const -> void;

    // sets a uniform mat4
    auto SetUniform(const std::string& name, const glm::mat4& value) const -> void;
    
private:
    uint32_t m_Id = 0;
};