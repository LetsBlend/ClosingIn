//
// Created by Let'sBlend on 11/03/2024.
//

#ifndef CLOSINGIN_RENDERER2D_H
#define CLOSINGIN_RENDERER2D_H

#include "SystemsManager/Layer.h"

#include "GraphicsAPI/RendererAPI.h"
#include "GraphicsAPI/Buffers.h"
#include "GraphicsAPI/VertexArray.h"
#include "GraphicsAPI/Shader.h"
#include "GraphicsAPI/Textures.h"

class Listener;

class Renderer2D : public Layer
{
public:
    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate() override;

    void OnWindowResize(Listener& listener);

private:
    // Temporary
    float vertices[32] {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };
    unsigned int indices[6] {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };

    Ref<RendererAPI> glAPI = RendererAPI::Create();

    Ref<VertexBuffer> vB = VertexBuffer::Create(vertices, sizeof(vertices));

    Ref<IndexBuffer> iB = IndexBuffer::Create(indices, sizeof(indices), 6);
    Ref<VertexArray> vA = VertexArray::Create();

    Ref<Shader> sh = Shader::Create("Assets/shaders/shader.glsl");
    Ref<Texture2D> t02D = Texture2D::Create("Assets/textures/cover.png");
    Ref<Texture2D> t12D = Texture2D::Create("Assets/textures/container.jpg");
};

#endif //CLOSINGIN_RENDERER2D_H
