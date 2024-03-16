//
// Created by Let'sBlend on 15/03/2024.
//

#ifndef CLOSINGIN_GRAPHICSCONTEXT_H
#define CLOSINGIN_GRAPHICSCONTEXT_H

class GLFWwindow;

class GraphicsContext
{
public:
    GraphicsContext() = default;
    virtual ~GraphicsContext() = default;

    static void GSetFlags();
    static void GSetWindow(GLFWwindow* window);
    static void GLoadGlad();
    static void GSwapBuffers();

private:
    virtual void SetFlags() = 0;
    virtual void SetWindow(GLFWwindow* window) = 0;
    virtual void LoadGlad() = 0;
    virtual void SwapBuffers() = 0;

    static Scope<GraphicsContext> Create();
    inline static Scope<GraphicsContext> graphicsContext = GraphicsContext::Create();
};


#endif //CLOSINGIN_GRAPHICSCONTEXT_H
