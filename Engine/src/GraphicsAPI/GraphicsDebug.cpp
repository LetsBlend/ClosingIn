//
// Created by Let'sBlend on 15/03/2024.
//

#include "GraphicsDebug.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLDebug.h"

Scope<GraphicsDebug> GraphicsDebug::Create()
{
    switch(RendererAPI::GetAPI())
    {
        case RendererAPI::API::None: std::cout << "No Rendering API enabled" << std::endl; // TODO: Assertion
        case RendererAPI::API::OpenGL: return CreateScope<OpenGLDebug>();
    }
    return nullptr;
}

void GraphicsDebug::GSetDebugFlags()
{
    graphicsDebug->SetDebugFlag();
}

void GraphicsDebug::GEnableDebug()
{
    graphicsDebug->EnableDebug();
}