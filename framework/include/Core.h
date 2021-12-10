#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <functional>
#include <filesystem>
#include <unordered_map>
#include <array>

namespace fs = std::filesystem;

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                        << " line " << __LINE__ << ": \n\n" << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)

template <class T>
using Scope = std::unique_ptr<T>;

template <class T, class... Types>
auto constexpr MakeScoped(Types&&... args) -> Scope<T>
{
    return std::make_unique<T>(std::forward<Types>(args)...);
}

template <class T>
using Ref = std::shared_ptr<T>;

template <class T, class... Types>
auto constexpr MakeRef(Types&&... args) -> Ref<T>
{
    return std::make_shared<T>(std::forward<Types>(args)...);
}

template <class T>
class Singelton
{
public:
    static auto Get() -> T&
    {
        static T instance;
        return instance;
    }

    Singelton(const Singelton&) = delete;
    Singelton(Singelton&&) = delete;
    auto operator = (const Singelton&) -> Singelton & = delete;

protected:
    Singelton() {}
    virtual ~Singelton() {}
};

template <class T>
class CreatableRef
{
public:
    template <class... Types>
    auto static Create(Types&&... args) -> Ref<T>
    {
        return std::make_shared<T>(std::forward<Types>(args)...);
    }
};