//
// Created by Let'sBlend on 11/03/2024.
//

#include "OpenGLContext.h"
#include "glad/glad.h"
#include "glfw/glfw3.h"

void OpenGLContext::SetWindow(GLFWwindow *window)
{
    m_Window = window;
}

void OpenGLContext::SetFlags()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void OpenGLContext::LoadGlad()
{
    int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // TODO: Assertion here
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_Window);
}
