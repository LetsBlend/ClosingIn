#//////////////////////////////////////////////////////////////////////////////////

cmake_minimum_required(VERSION 3.26)

#//////////////////////////////////////////////////////////////////////////////////

project(Engine)

set(CMAKE_CXX_STANDARD 20)

include_directories(Engine/src Engine/vendor/glm Engine/vendor/glfw/include Engine/vendor/glad/include Engine/vendor/imgui Engine/vendor)

add_subdirectory(Engine/vendor/glfw)
add_subdirectory(Engine/vendor/glad)
add_subdirectory(Engine/vendor/imgui)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("debug mode")
    add_compile_definitions(DEBUG)
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    message("release mode")
    add_compile_definitions(RELEASE)
elseif (CMAKE_BUILD_TYPE MATCHES Dist)
    message("distribution mode")
    add_compile_definitions(DIST)
endif(CMAKE_BUILD_TYPE MATCHES Debug)

if(WIN32)
    add_compile_definitions(PLATFORM_WINDOWS)
elseif (UNIX)
    add_compile_definitions(PLATFORM_LINUX)
elseif (APPLE)
    add_compile_definitions(PLATFORM_MAC)
endif (WIN32)

add_compile_definitions(GLFW_INCLUDE_NONE)

add_library(Engine
        Engine/src/Events/Event.cpp
        Engine/src/Events/Event.h
        Engine/src/Events/Input.cpp
        Engine/src/Events/Input.h
        Engine/includes/EngineAPI.h
        Engine/src/Engine.cpp
        Engine/src/Engine.h
        Engine/src/EntryPoint.h
        Engine/src/SystemsManager/Layer.h
        Engine/src/SystemsManager/Scene.h
        Engine/src/SystemsManager/LayerStack.cpp
        Engine/src/SystemsManager/LayerStack.h
        Engine/src/SystemsManager/SceneStack.cpp
        Engine/src/SystemsManager/SceneStack.h
        Engine/src/Window/Window.cpp
        Engine/src/Window/Window.h
        Engine/includes/EngineInit.h
        Engine/src/Events/EventType.h
        Engine/src/Math/Math.h
        Engine/src/EngineTime.h
        Engine/src/EngineTime.cpp
        Engine/src/Defines.h
        Engine/src/Renderer/Renderer2D/Renderer2D.cpp
        Engine/src/Renderer/Renderer2D/Renderer2D.h
        Engine/src/GraphicsAPI/OpenGL/OpenGLContext.cpp
        Engine/src/GraphicsAPI/OpenGL/OpenGLContext.h
        Engine/src/GraphicsAPI/OpenGL/OpenGLRendererAPI.cpp
        Engine/src/GraphicsAPI/OpenGL/OpenGLRendererAPI.h
        Engine/src/GraphicsAPI/OpenGL/OpenGLBuffers.cpp
        Engine/src/GraphicsAPI/OpenGL/OpenGLBuffers.h
        Engine/src/GraphicsAPI/OpenGL/OpenGLShader.cpp
        Engine/src/GraphicsAPI/OpenGL/OpenGLShader.h
        Engine/src/GraphicsAPI/OpenGL/OpenGLVertexArray.cpp
        Engine/src/GraphicsAPI/OpenGL/OpenGLVertexArray.h
        Engine/src/GraphicsAPI/OpenGL/OpenGLDebug.cpp
        Engine/src/GraphicsAPI/OpenGL/OpenGLDebug.h
        Engine/vendor/stb/stb_image.h
        Engine/src/GraphicsAPI/OpenGL/OpenGLTextures.cpp
        Engine/src/GraphicsAPI/OpenGL/OpenGLTextures.h
        Engine/src/GraphicsAPI/Buffers.cpp
        Engine/src/GraphicsAPI/Buffers.h
        Engine/src/GraphicsAPI/RendererAPI.cpp
        Engine/src/GraphicsAPI/RendererAPI.h
        Engine/src/GraphicsAPI/VertexArray.cpp
        Engine/src/GraphicsAPI/VertexArray.h
        Engine/src/GraphicsAPI/Textures.cpp
        Engine/src/GraphicsAPI/Textures.h
        Engine/src/GraphicsAPI/Shader.cpp
        Engine/src/GraphicsAPI/Shader.h
        Engine/src/GraphicsAPI/GraphicsContext.cpp
        Engine/src/GraphicsAPI/GraphicsContext.h
        Engine/src/GraphicsAPI/GraphicsDebug.cpp
        Engine/src/GraphicsAPI/GraphicsDebug.h
        Engine/src/GraphicsAPI/Gui/GlfwGui.cpp
        Engine/src/GraphicsAPI/Gui/GlfwGui.h
        Engine/src/GraphicsAPI/OpenGL/OpenGLGUI/OpenGLGui.cpp
        Engine/src/GraphicsAPI/OpenGL/OpenGLGUI/OpenGLGui.h
        Engine/src/GraphicsAPI/Gui/GuiLayer.cpp
        Engine/src/GraphicsAPI/Gui/GuiLayer.h
        Engine/src/Renderer/ClearRender.cpp
        Engine/src/Renderer/ClearRender.h
        Engine/src/Renderer/EditorGui.cpp
        Engine/src/Renderer/EditorGui.h
        Engine/src/GraphicsAPI/Gui/GuiHandle.cpp
        Engine/src/GraphicsAPI/Gui/GuiHandle.h)
target_precompile_headers(Engine PUBLIC Engine/src/pch.h)

#//////////////////////////////////////////////////////////////////////////////////

project(ClosingIn)

set(CMAKE_CXX_STANDARD 20)

include_directories(ClosingIn/src Engine/includes)

add_executable(ClosingIn
        ClosingIn/main.cpp
        ClosingIn/Level-GreenHill/GameLayer.cpp
        ClosingIn/Level-GreenHill/GameLayer.h)
target_link_libraries(ClosingIn PRIVATE Engine glfw glad imgui)

#//////////////////////////////////////////////////////////////////////////////////