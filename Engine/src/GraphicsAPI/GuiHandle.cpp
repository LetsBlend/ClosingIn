//
// Created by Let'sBlend on 16/03/2024.
//

#include "GuiHandle.h"
#include "GraphicsAPI/GlfwGui/GlfwGui.h"
#include "GraphicsAPI/OpenGL/OpenGLGui/OpenGLGui.h"

#include "Events/Event.h"
#include "Window/Window.h"
#include "GraphicsAPI/RendererAPI.h"

GuiHandle::GuiHandle()
{
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.BackendFlags |= ImGuiConfigFlags_NavEnableGamepad;

    io.BackendFlags |= ImGuiConfigFlags_DockingEnable;
    io.BackendFlags |= ImGuiConfigFlags_NavEnableGamepad;

    switch (RendererAPI::GetAPI())
    {
        case RendererAPI::API::None: // TODO: Assertion here
            std::cout << "No API was specified!" << std::endl;
            break;
        case RendererAPI::API::OpenGL:
            ImGuiInit = &ImGui_ImplOpenGL3_Init;
            ImGuiGlfwInit = &ImGui_ImplGlfw_InitForOpenGL;
            ImGuiShutDown = &ImGui_ImplOpenGL3_Shutdown;
            ImGuiGlfwShutDown = &ImGui_ImplGlfw_Shutdown;
            break;
    }

    ImGuiGlfwInit(Window::GetWindow(), true);
    ImGuiInit("#version 410");
}

GuiHandle::~GuiHandle()
{
    ImGuiShutDown();
    ImGuiGlfwShutDown();
    ImGui::DestroyContext();
}
