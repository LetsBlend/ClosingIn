//
// Created by Let'sBlend on 12/03/2024.
//

#include "OpenGLVertexArray.h"
#include "glad/glad.h"

OpenGLVertexArray::OpenGLVertexArray()
{
    glGenVertexArrays(1, &vertexArrayID);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &vertexArrayID);
}

void OpenGLVertexArray::SetLayout()
{
    // vertex Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void OpenGLVertexArray::Bind()
{
    glBindVertexArray(vertexArrayID);
}

void OpenGLVertexArray::UnBind()
{
    glBindVertexArray(0);
}

uint32 OpenGLVertexArray::GetID()
{
    return vertexArrayID;
}
