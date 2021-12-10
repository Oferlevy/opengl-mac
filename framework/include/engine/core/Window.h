#pragma once

#include "Core.h"
#include "engine/events/Event.h"
#include "engine/events/WindowEvents.h"
#include "engine/events/KeyboardEvents.h"
#include "engine/events/MouseEvents.h"

class Window
{
public:
    Window(const std::string& title, glm::uvec2 size, const std::function<void(Event&)>& callback);
    ~Window();

    auto static Create(const std::string& title, glm::uvec2 size, const std::function<void(Event&)>& callback) -> Scope<Window>;

    auto Update() -> void;
    auto GetNativeWindow() const -> const GLFWwindow*;

    auto GetWidth() const -> uint32_t;
    auto GetHeight() const -> uint32_t;
    auto GetSize() const -> glm::uvec2;
    auto GetAspectRatio() const -> float;
    auto GetTitle() const -> const std::string&;

    auto SetWidth(uint32_t width) -> void;
    auto SetHeight(uint32_t height) -> void;
    auto SetSize(glm::uvec2 width) -> void;
    auto SetTitle(const std::string& title) -> void;

private:
    auto InitImGui() const -> void;
    auto InitEventCallbacks() const -> void;
    
private:
    glm::uvec2 m_Size = { 0, 0 };
    std::string m_Title = "";
    std::function<void(Event&)> m_EventCallback;
    
    GLFWwindow* m_Window = nullptr;
};