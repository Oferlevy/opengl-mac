#include "engine/renderer/Renderer.h"

auto Renderer::Init(const GLFWwindow* window) -> void
{
    Get().m_Window = const_cast<GLFWwindow*>(window);
    
    ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW!");
}

auto Renderer::Clear() -> void
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

auto Renderer::SwapBuffers() -> void
{
    ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(reinterpret_cast<GLFWwindow*>(Get().m_Window));
}

auto Renderer::SetClearColor(const glm::vec4& color) -> void
{
    glClearColor(color.r, color.g, color.b, color.a);
}

auto Renderer::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) -> void
{
    glViewport(x, y, width, height);
}

auto Renderer::DrawIndexed(const Ref<VertexArray>& vertexArray) -> void
{
    vertexArray->Bind();
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}