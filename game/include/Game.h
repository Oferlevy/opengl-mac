#pragma once

#include <Framework.h>

class Game : public Layer
{
public:
    auto OnAttach() -> void override;
    auto OnDetach() -> void override;
    auto OnEvent(const Event& e) -> void override;
    auto OnUpdate(float deltaTime) -> void override;
    auto OnImGuiRender() -> void override;
};