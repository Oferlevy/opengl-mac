#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "engine/renderer/Renderer.h"

class Application : public LayerStack
{
public:
    Application() = default;
    virtual ~Application() = default;

    auto Run() -> void;

private:
    auto OnEvent(Event& e) -> void;

private:
    bool m_Running = true;
    Scope<Window> m_Window;
};