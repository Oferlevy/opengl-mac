#pragma once

#include "Core.h"
#include "VertexArray.h"

class Renderer : public Singelton<Renderer>
{
public:
    auto static Init(const GLFWwindow* window) -> void;
    auto static Clear() -> void;
    auto static SwapBuffers() -> void;
    auto static SetClearColor(const glm::vec4& color) -> void;
    auto static SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) -> void;

    auto static DrawIndexed(const Ref<VertexArray>& vertexArray) -> void;

private:
    GLFWwindow* m_Window = nullptr;
};