//
// Created by Let'sBlend on 15/03/2024.
//

#include "RendererAPI.h"
#include "OpenGL/OpenGLRendererAPI.h"

Scope<RendererAPI> RendererAPI::Create()
{
    switch (RendererAPI::GetAPI())
    {
        case RendererAPI::API::None:
            std::cout << "No Rendering API enabled" << std::endl; // TODO: Assertion
        case RendererAPI::API::OpenGL:
            return CreateScope<OpenGLRendererAPI>();
    }
    return nullptr;
}

void RendererAPI::GSetFlags()
{
    s_rendererApi->SetFlags();
}

void RendererAPI::GSetViewport(uint16 posX, uint16 posY, uint16 width, uint16 height)
{
    s_rendererApi->SetViewport(posX, posY, width, height);
}

void RendererAPI::GDrawIndexed(uint32 indexCount)
{
    s_rendererApi->DrawIndexed(indexCount);
}

void RendererAPI::GClearColor(const Math::vec4 &color)
{
    s_rendererApi->ClearColor(color);
}

void RendererAPI::GClear()
{
    s_rendererApi->Clear();
}