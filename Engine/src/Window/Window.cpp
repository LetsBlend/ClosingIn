//
// Created by Let'sBlend on 04/03/2024.
//

#include "Window.h"
#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Events/Event.h"

#include "GraphicsAPI/GraphicsContext.h"

Window::Window(const std::string &name, const int &width, const int &height)
{
    data.name = name;
    data.width = width;
    data.height = height;

    if(!glfwInit())
        return; // <- Assertions please Daddy, assert me harder

    GraphicsContext::GSetFlags();

    window = glfwCreateWindow(data.width, data.height, data.name.c_str(), nullptr, nullptr);

    GraphicsContext::GSetWindow(window);

    if(!window)
    {
        glfwTerminate();
        return; // <- TODO: Die Assertions Bruuuuddaaaaa
    }

    glfwMakeContextCurrent(window);

    GraphicsContext::GLoadGlad();

    glfwSetWindowUserPointer(window, &data);
    SetVSync(data.vsync);

    glfwSetWindowCloseCallback(window, [](GLFWwindow* callback)
    {
        Event::PushEvent(EventType::WindowClose);
    });
    glfwSetWindowSizeCallback(window, [](GLFWwindow* callback, int width, int height)
    {
        auto* pData = (WindowData*)glfwGetWindowUserPointer(callback);
        pData->width = width;
        pData->height = height;

        EventContext e{};
        e.ui16[0] = width;
        e.ui16[1] = height;
        Event::PushEvent(EventType::WindowResize, e);
    });
    glfwSetWindowPosCallback(window, [](GLFWwindow* callback, int xpos, int ypos)
    {
        auto* pData = (WindowData*)glfwGetWindowUserPointer(callback);
        pData->posX = xpos;
        pData->posY = ypos;

        EventContext e{};
        e.ui16[0] = xpos;
        e.ui16[1] = ypos;
        Event::PushEvent(EventType::WindowMoved, e);
    });
    glfwSetWindowFocusCallback(window, [](GLFWwindow* callback, int focused)
    {
        auto* pData = (WindowData*)glfwGetWindowUserPointer(callback);
        pData->focused = focused;

        EventContext e{};
        e.i8[0] = (int8_t)focused;
        Event::PushEvent(EventType::WindowFocus, e);
    });
    glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int codepoint)
    {
        EventContext e{};
        e.ui32[0] = codepoint;
        Event::PushEvent(EventType::TextInput, e);
    });
    glfwSetKeyCallback(window, [](GLFWwindow* callback, int key, int scancode, int action, int mods)
    {
        EventContext e{};

        switch(action)
        {
            case GLFW_PRESS:
                e.i8[0] = (int8_t)key;
                Event::PushEvent(EventType::KeyPressed, e);
                break;
            case GLFW_RELEASE:
                e.i8[0] = (int8_t)key;
                Event::PushEvent(EventType::KeyReleased, e);
                break;
            case GLFW_REPEAT:
                e.i8[0] = (int8_t)key;
                Event::PushEvent(EventType::KeyPressed, e);
                break;
        }
    });
    glfwSetMouseButtonCallback(window, [](GLFWwindow* callback, int button, int action, int mods)
    {
        EventContext e{};

        switch (action)
        {
            case GLFW_PRESS:
                e.i8[0] = (int8_t)button;
                Event::PushEvent(EventType::KeyPressed, e);
                break;
            case GLFW_RELEASE:
                e.i8[0] = (int8_t)button;
                Event::PushEvent(EventType::KeyReleased, e);
                break;
            case GLFW_REPEAT:
                e.i8[0] = (int8_t)button;
                Event::PushEvent(EventType::KeyPressed, e);
                break;
        }
    });
    glfwSetCursorPosCallback(window, [](GLFWwindow* callback, double xpos, double ypos)
    {
        EventContext e{};
        e.f32[0] = (float)xpos;
        e.f32[1] = (float)ypos;
        Event::PushEvent(EventType::MouseMoved, e);
    });
    glfwSetScrollCallback(window, [](GLFWwindow* callback, double xoffset, double yoffset)
    {
        EventContext e{};
        e.f32[0] = (float)xoffset;
        e.f32[1] = (float)yoffset;
        Event::PushEvent(EventType::MouseScrolled, e);
    });

    // To Set the viewport
    EventContext e{};
    e.ui16[0] = width;
    e.ui16[1] = height;
    Event::PushEvent(EventType::WindowResize, e);
}

Window::~Window()
{
    glfwTerminate();
}

void Window::OnUpdate()
{
    glfwPollEvents();
    Event::FireEvents();
    GraphicsContext::GSwapBuffers();
}

void Window::SetVSync(const bool& enabled)
{
    glfwSwapInterval(enabled);
}

bool Window::IsVSync()
{
    return data.vsync;
}

void Window::SetSize(const uint16_t& width, const uint16_t& height)
{
    data.width = width;
    data.height = height;
}

void Window::SetFocus(const bool &focused)
{
    data.focused = focused;
}

GLFWwindow *Window::GetWindow()
{
    return window;
}

