//
// Created by Let'sBlend on 15/03/2024.
//

#include "Buffers.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLBuffers.h"

Ref<VertexBuffer> VertexBuffer::Create(const void *vertices, uint32 size)
{
    switch(RendererAPI::GetAPI())
    {
        case RendererAPI::API::None: std::cout << "No Rendering API enabled" << std::endl; // TODO: Assertion
        case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);
    }
    return nullptr;
}

Ref<IndexBuffer> IndexBuffer::Create(const void *indices, uint32 size, uint32 count)
{
    switch(RendererAPI::GetAPI())
    {
        case RendererAPI::API::None: std::cout << "No Rendering API enabled" << std::endl; // TODO: Assertion
        case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, size, count);
    }
    return nullptr;
}
