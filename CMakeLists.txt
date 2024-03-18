#//////////////////////////////////////////////////////////////////////////////////

cmake_minimum_required(VERSION 3.26)

#//////////////////////////////////////////////////////////////////////////////////

project(Engine)

set(CMAKE_CXX_STANDARD 20)

include_directories(Engine/src Engine/vendor/glm Engine/vendor/glfw/include Engine/vendor/glad/include)

add_subdirectory(Engine/vendor/glfw)
add_subdirectory(Engine/vendor/glad)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_BUILD_TYPE Debug)
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
        Engine/src/Math/Math.h
        Engine/src/Util/ConsoleColours.h
        Engine/src/Util/ConsoleColours.h
        Engine/src/Debug/Logger.cpp
        Engine/src/Debug/Logger.h
        Engine/src/Debug/Assert.cpp
        Engine/src/Debug/Assert.h
        Engine/src/Window/Window.cpp
        Engine/src/Window/Window.h
        Engine/includes/EngineInit.h
        Engine/src/Events/EventType.h
        Engine/src/Math/Math.h
        Engine/src/EngineTime.h
        Engine/src/EngineTime.cpp
        Engine/src/Defines.h
        Engine/src/Renderer/Renderer.cpp
        Engine/src/Renderer/Renderer.h
        Engine/src/Renderer/OpenGL/OpenGLContext.cpp
        Engine/src/Renderer/OpenGL/OpenGLContext.h
        Engine/src/Renderer/OpenGL/OpenGLRendererAPI.cpp
        Engine/src/Renderer/OpenGL/OpenGLRendererAPI.h
        Engine/src/Renderer/OpenGL/OpenGLBuffers.cpp
        Engine/src/Renderer/OpenGL/OpenGLBuffers.h
        Engine/src/Renderer/OpenGL/OpenGLShaders.cpp
        Engine/src/Renderer/OpenGL/OpenGLShaders.h
        Engine/src/Renderer/OpenGL/OpenGLVertexArray.cpp
        Engine/src/Renderer/OpenGL/OpenGLVertexArray.h)
        
target_precompile_headers(Engine PUBLIC Engine/src/pch.h)

#//////////////////////////////////////////////////////////////////////////////////

project(ClosingIn)

set(CMAKE_CXX_STANDARD 20)

include_directories(ClosingIn/src Engine/includes)

add_executable(ClosingIn
        ClosingIn/main.cpp
        ClosingIn/Level-GreenHill/GameLayer.cpp
        ClosingIn/Level-GreenHill/GameLayer.h)
target_link_libraries(ClosingIn PRIVATE Engine glfw glad)

#//////////////////////////////////////////////////////////////////////////////////