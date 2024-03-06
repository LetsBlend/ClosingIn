//
// Created by Let'sBlend on 04/03/2024.
//

#ifndef CLOSING_WINDOW_H
#define CLOSING_WINDOW_H

class GLFWwindow;

class Window
{
public:
    Window() = default;
    ~Window() = default;

    void StartUp(std::string&& name, int&& xpos, int&& ypos);
    void ShutDown();

    void Update();

    void SetSize(const uint16_t& width, const uint16_t& height);
    void SetFocus(const bool& focused);
    void SetVSync(const bool& enabled);
    bool IsVSync();

    GLFWwindow* GetWindow();

private:
    struct WindowData
    {
        std::string name = "No Name";
        bool vsync = true;
        int focused = 1;

        uint16_t width = 640;
        uint16_t height = 480;

        uint16_t posX = 640;
        uint16_t posY = 480;
    };

    GLFWwindow* window;
    WindowData data;
};


#endif //CLOSING_WINDOW_H