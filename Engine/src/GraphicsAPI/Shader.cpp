//
// Created by Let'sBlend on 15/03/2024.
//

#include "Shader.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLShader.h"

Ref<Shader> Shader::Create(const std::string &filePath)
{
    switch(RendererAPI::GetAPI())
    {
        case RendererAPI::API::None: std::cout << "No Rendering API enabled" << std::endl; // TODO: Assertion
        case RendererAPI::API::OpenGL: return CreateScope<OpenGLShader>(filePath);
    }
    return nullptr;
}
