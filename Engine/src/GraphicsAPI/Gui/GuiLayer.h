//
// Created by Let'sBlend on 16/03/2024.
//

#ifndef CLOSINGIN_GUILAYER_H
#define CLOSINGIN_GUILAYER_H

#include "imgui.h"
#include "SystemsManager/Layer.h"

class Listener;
class GLFWwindow;

class GuiLayer : public Layer
{
public:
    GuiLayer();
    ~GuiLayer() override;

    void OnAttach() override {};
    void OnDetach() override {};
    void OnUpdate() override;
    virtual void OnGui() {};

private:
    void (*ImGuiNewFrame)() = nullptr;
    void (*ImGuiGlfwNewFrame)() = nullptr;
    void (*ImGuiRenderDrawData)(ImDrawData* draw_data) = nullptr;

    GLFWwindow* window;

    uint16 width;
    uint16 height;
};

namespace Gui
{
    using namespace ImGui;
}

#endif //CLOSINGIN_GUILAYER_H
