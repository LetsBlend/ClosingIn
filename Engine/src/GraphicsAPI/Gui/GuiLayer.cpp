//
// Created by Let'sBlend on 16/03/2024.
//

#include "GuiLayer.h"
#include "GlfwGui.h"
#include "GraphicsAPI/OpenGL/OpenGLGUI/OpenGLGui.h"

#include "GraphicsAPI/RendererAPI.h"

GuiLayer::GuiLayer()
{
    switch (RendererAPI::GetAPI())
    {
        case RendererAPI::API::None: // TODO: Assertion here
            std::cout << "No API was specified!" << std::endl;
            break;
        case RendererAPI::API::OpenGL:
            ImGuiNewFrame = &ImGui_ImplOpenGL3_NewFrame;
            ImGuiGlfwNewFrame = &ImGui_ImplGlfw_NewFrame;
            ImGuiRenderDrawData = &ImGui_ImplOpenGL3_RenderDrawData;
            break;
    }
}

GuiLayer::~GuiLayer()
{

}

void GuiLayer::OnUpdate()
{
    ImGuiNewFrame();
    ImGuiGlfwNewFrame();
    ImGui::NewFrame();

    OnGui();

    ImGui::Render();
    ImGuiRenderDrawData(ImGui::GetDrawData());
}
