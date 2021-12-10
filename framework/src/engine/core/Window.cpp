#include "engine/core/Window.h"

Window::Window(const std::string& title, glm::uvec2 size, const std::function<void(Event&)>& callback)
    : m_Title(title), m_Size(size), m_EventCallback(callback)
{
    ASSERT(glfwInit(), "Failed to initialize GLFW!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    m_Window = glfwCreateWindow(m_Size.x, m_Size.y, m_Title.c_str(), nullptr, nullptr);
    ASSERT(m_Window, "Failed to create GLFW window!");

    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, this);
    glfwSwapInterval(1);

    InitImGui();
    InitEventCallbacks();
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

auto Window::Create(const std::string& title, glm::uvec2 size, const std::function<void(Event&)>& callback) -> Scope<Window>
{
    return MakeScoped<Window>(title, size, callback);
}

auto Window::Update() -> void
{
	glfwPollEvents();
}

auto Window::GetNativeWindow() const -> const GLFWwindow*
{
    return m_Window;
}

auto Window::GetWidth() const -> uint32_t
{
    return m_Size.x;
}

auto Window::GetHeight() const -> uint32_t
{
    return m_Size.y;
}

auto Window::GetSize() const -> glm::uvec2
{
    return m_Size;
}

auto Window::GetAspectRatio() const -> float
{
    return m_Size.y ? static_cast<float>(m_Size.x) / static_cast<float>(m_Size.y) : 0.0f;
}

auto Window::GetTitle() const -> const std::string&
{
    return m_Title;
}

auto Window::SetWidth(uint32_t width) -> void
{
    SetSize({ width, m_Size.y });
}

auto Window::SetHeight(uint32_t height) -> void
{
    SetSize({ m_Size.x, height });
}

auto Window::SetSize(glm::uvec2 size) -> void
{
    m_Size = size;
    glfwSetWindowSize(m_Window, m_Size.x, m_Size.y);
}

auto Window::SetTitle(const std::string& title) -> void
{
    m_Title = title;
    glfwSetWindowTitle(m_Window, m_Title.c_str());
}

auto Window::InitImGui() const -> void
{
    ImGui::CreateContext();
	auto& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 410 core");

	// Changing the default ImGui font.
	io.Fonts->AddFontFromFileTTF("framework/res/fonts/OpenSans-Regular.ttf", 16.0f);

	auto& colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = { 0.1f, 0.105f, 0.11f, 1.0f };

	// Headers
	colors[ImGuiCol_Header] = { 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_HeaderHovered] = { 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_HeaderActive] = { 0.15f, 0.1505f, 0.151f, 1.0f };

	// Buttons
	colors[ImGuiCol_Button] = { 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_ButtonHovered] = { 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_ButtonActive] = { 0.15f, 0.1505f, 0.151f, 1.0f };

	// Frame BG
	colors[ImGuiCol_FrameBg] = { 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_FrameBgHovered] = { 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_FrameBgActive] = { 0.15f, 0.1505f, 0.151f, 1.0f };

	// Tabs
	colors[ImGuiCol_Tab] = { 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TabHovered] = { 0.38f, 0.3805f, 0.381f, 1.0f };
	colors[ImGuiCol_TabActive] = { 0.28f, 0.2805f, 0.281f, 1.0f };
	colors[ImGuiCol_TabUnfocused] = { 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TabUnfocusedActive] = { 0.2f, 0.205f, 0.21f, 1.0f };

	// Title
	colors[ImGuiCol_TitleBg] = { 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TitleBgActive] = { 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TitleBgCollapsed] = { 0.15f, 0.1505f, 0.151f, 1.0f };
}

auto Window::InitEventCallbacks() const -> void
{
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* win, int width, int height) {
        auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win));
        auto e = WindowResizedEvent({ width, height });
        window->m_Size = { width, height };
        window->m_EventCallback(e);
    });

    glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow* win, int maximized) {
        auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win));
        auto e = WindowMaximizedEvent();
        window->m_EventCallback(e);
        });

    glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* win, int focuesd) {
        auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win));

        if (focuesd)
        {
            auto e = WindowGainedFocusEvent();
            window->m_EventCallback(e);
        }
        else
        {
            auto e = WindowLostFocusEvent();
            window->m_EventCallback(e);
        }
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* win) {
        auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win));
        auto e = WindowClosedEvent();
        window->m_EventCallback(e);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
        auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win));

        switch (action)
        {
        case GLFW_PRESS:
        {
            auto e = KeyPressedEvent(static_cast<Key>(key));
            window->m_EventCallback(e);
            break;
        }
        case GLFW_RELEASE:
        {
            auto e = KeyReleasedEvent(static_cast<Key>(key));
            window->m_EventCallback(e);
            break;
        }
        }
    });

    glfwSetCharCallback(m_Window, [](GLFWwindow* win, uint32_t text) {
        auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win));
        auto e = KeyTypedEvent(static_cast<Key>(text));
        window->m_EventCallback(e);
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* win, int button, int action, int mods) {
        auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win));
        

        switch (action)
        {
        case GLFW_PRESS:
        {
            auto e = MousePressedEvent(static_cast<MouseButton>(button));
            window->m_EventCallback(e);
            break;
        }
        case GLFW_RELEASE:
        {
            auto e = MouseReleasedEvent(static_cast<MouseButton>(button));
            window->m_EventCallback(e);
            break;
        }
        }
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* win, double x, double y) {
        auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win));
        auto e = MouseMovedEvent({ x, y });
        window->m_EventCallback(e);
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* win, double xOffset, double yOffset) {
        auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win));
        auto e = MouseScrolledEvent(static_cast<float>(yOffset));
        window->m_EventCallback(e);
    });
}