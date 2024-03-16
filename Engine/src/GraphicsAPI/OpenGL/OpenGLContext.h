//
// Created by Let'sBlend on 11/03/2024.
//

#ifndef CLOSINGIN_OPENGLCONTEXT_H
#define CLOSINGIN_OPENGLCONTEXT_H

#include "GraphicsAPI/GraphicsContext.h"

class GLFWwindow;

class OpenGLContext : public GraphicsContext
{
public:
    OpenGLContext() = default;
    ~OpenGLContext() override = default;

    void SetFlags() override;
    void SetWindow(GLFWwindow* window) override;
    void LoadGlad() override;
    void SwapBuffers() override;

private:
    GLFWwindow* m_Window;
};

#endif //CLOSINGIN_OPENGLCONTEXT_H