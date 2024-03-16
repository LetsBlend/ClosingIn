//
// Created by Let'sBlend on 11/03/2024.
//

#include "OpenGLRendererAPI.h"
#include "glad/glad.h"

void OpenGLRendererAPI::SetFlags()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}

void OpenGLRendererAPI::SetViewport(uint16 posX, uint16 posY, uint16 width, uint16 height)
{
    glViewport(posX, posY, width, height);
}

void OpenGLRendererAPI::DrawIndexed(uint32 indexCount)
{
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

void OpenGLRendererAPI::ClearColor(const glm::vec4 &color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
