#pragma once

#include "Core.h"
#include "engine/events/Event.h"

class Layer
{
public:
    Layer() = default;
    virtual ~Layer() {}

    auto virtual OnAttach() -> void {}
    auto virtual OnDetach() -> void {}
    auto virtual OnEvent(const Event& e) -> void {}
    auto virtual OnUpdate(float deltaTime) -> void {}
    auto virtual OnImGuiRender() -> void {}
};