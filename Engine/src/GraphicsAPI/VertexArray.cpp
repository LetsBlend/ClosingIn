//
// Created by Let'sBlend on 15/03/2024.
//

#include "VertexArray.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLVertexArray.h"

Ref<VertexArray> VertexArray::Create()
{
    switch(RendererAPI::GetAPI())
    {
        case RendererAPI::API::None: std::cout << "No Rendering API enabled" << std::endl; // TODO: Assertion
        case RendererAPI::API::OpenGL: return CreateScope<OpenGLVertexArray>();
    }
    return nullptr;
}
