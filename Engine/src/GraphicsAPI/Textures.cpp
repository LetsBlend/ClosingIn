//
// Created by Let'sBlend on 15/03/2024.
//

#include "Textures.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLTextures.h"

Ref<Texture2D> Texture2D::Create(const std::string& filePath)
{
    switch(RendererAPI::GetAPI())
    {
        case RendererAPI::API::None: std::cout << "No Rendering API enabled" << std::endl; // TODO: Assertion
        case RendererAPI::API::OpenGL: return CreateScope<OpenGLTexture2D>(filePath);
    }
    return nullptr;
}
