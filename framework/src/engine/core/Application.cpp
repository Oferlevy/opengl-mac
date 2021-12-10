#include "engine/core/Application.h"

auto Application::Run() -> void
{
    // initializes the window and renderer
    m_Window = Window::Create("Application", { 800, 480 }, BIND_EVENT_FN(OnEvent));
    Renderer::Init(m_Window->GetNativeWindow());
    
    // initializes the layers
    for (const auto& layer : m_Layers)
        layer->OnAttach();

    // for delta time
    auto previousFrame = glfwGetTime();

    while (m_Running)
    {
        Renderer::Clear();

        // calculates delta time
        auto now = glfwGetTime();
        auto deltaTime = static_cast<float>(now - previousFrame);
        previousFrame = now;

        // updates the layers
        for (const auto& layer : m_Layers)
        {
            layer->OnUpdate(deltaTime);
            layer->OnImGuiRender();
        }

        // updates the window and renderer
        Renderer::SwapBuffers();
        m_Window->Update();
    }
}

auto Application::OnEvent(Event& e) -> void
{
    auto dispatcher = EventDispatcher(e);

    // updates the viewport
    dispatcher.Dispatch<WindowResizedEvent>([this](WindowResizedEvent& e) {
        Renderer::SetViewport(0, 0, e.GetWidth(), e.GetHeight());
        return false;
    });

    // stops the application when the 'X' is clicked
    dispatcher.Dispatch<WindowClosedEvent>([this](WindowClosedEvent& e) {
        m_Running = false;
        return false;
    });

    // loops over the layers reversed
    for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); it++)
    {
        if (e.m_Handled)
            break;

        (*it)->OnEvent(e);
    }
}