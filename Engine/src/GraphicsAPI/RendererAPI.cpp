//
// Created by Let'sBlend on 15/03/2024.
//

#include "RendererAPI.h"
#include "OpenGL/OpenGLRendererAPI.h"

Scope<RendererAPI> RendererAPI::Create()
{
    switch(RendererAPI::GetAPI())
    {
        case RendererAPI::API::None: std::cout << "No Rendering API enabled" << std::endl; // TODO: Assertion
        case RendererAPI::API::OpenGL: return CreateScope<OpenGLRendererAPI>();
    }
    return nullptr;
}
