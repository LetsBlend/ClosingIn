//
// Created by Let'sBlend on 16/03/2024.
//

#ifndef CLOSINGIN_GUIHANDLE_H
#define CLOSINGIN_GUIHANDLE_H

#include "imgui.h"

class GLFWwindow;

class GuiHandle
{
public:
    GuiHandle();
    ~GuiHandle();

private:
    bool (*ImGuiInit)(const char* glsl_version) = nullptr;
    bool (*ImGuiGlfwInit)(GLFWwindow* window, bool install_callbacks) = nullptr;
    void (*ImGuiShutDown)() = nullptr;
    void (*ImGuiGlfwShutDown)() = nullptr;
};


#endif //CLOSINGIN_GUIHANDLE_H
