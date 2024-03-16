//
// Created by Let'sBlend on 11/03/2024.
//

#ifndef CLOSINGIN_OPENGLRENDERERAPI_H
#define CLOSINGIN_OPENGLRENDERERAPI_H

#include "GraphicsAPI/RendererAPI.h"

class GLFWwindow;

class OpenGLRendererAPI : public RendererAPI
{
public:
    OpenGLRendererAPI() = default;
    ~OpenGLRendererAPI() override = default;

    void SetFlags() override;
    void SetViewport(uint16 posX, uint16 posY, uint16 width, uint16 height) override;

    void DrawIndexed(uint32 indexCount) override;

    void ClearColor(const Math::vec4& color) override;
    void Clear() override;
};

#endif //CLOSINGIN_OPENGLRENDERERAPI_H
