//
// Created by Let'sBlend on 15/03/2024.
//

#include "GraphicsContext.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLContext.h"
#include "GraphicsDebug.h"

Scope<GraphicsContext> GraphicsContext::Create()
{
    switch(RendererAPI::GetAPI())
    {
        case RendererAPI::API::None: std::cout << "No Rendering API enabled" << std::endl; // TODO: Assertion
        case RendererAPI::API::OpenGL: return CreateScope<OpenGLContext>();
    }
    return nullptr;
}

void GraphicsContext::GSetFlags()
{
    s_graphicsContext->SetFlags();
    GraphicsDebug::GSetDebugFlags();
}

void GraphicsContext::GSetWindow(GLFWwindow *window)
{
    s_graphicsContext->SetWindow(window);
}

void GraphicsContext::GLoadGlad()
{
    s_graphicsContext->LoadGlad();
    GraphicsDebug::GEnableDebug();
}

void GraphicsContext::GSwapBuffers()
{
    s_graphicsContext->SwapBuffers();
}
