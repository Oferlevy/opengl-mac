#pragma once

#include "Core.h"
#include "Layer.h"

template <class T>
concept LayerType = std::is_base_of<Layer, T>::value;

class LayerStack
{
public:
    friend class Application;

protected:
    template <LayerType T, class... Args>
    auto PushLayer(Args&&... args) -> void
    {
        m_Layers.insert(m_Layers.begin() + m_OverlayStart, MakeRef<T>(std::forward<Args>(args)...));
        m_OverlayStart++;
    }

    template <LayerType T, class... Args>
    auto PushOverlay(Args&&... args) -> void
    {
        m_Layers.push_back(MakeRef<T>(std::forward<Args>(args)...));
    }

private:
    std::vector<Ref<Layer>> m_Layers;
    uint32_t m_OverlayStart = 0;
};