//
// Created by Let'sBlend on 12/03/2024.
//

#include "OpenGLBuffers.h"
#include "glad/glad.h"

/////////////////////////////////////////////////////////////////////
// Vertex Buffer
/////////////////////////////////////////////////////////////////////

OpenGLVertexBuffer::OpenGLVertexBuffer(const void* vertices, uint32 size)
{
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &vertexBufferID);
}

void OpenGLVertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
}

void OpenGLVertexBuffer::UnBind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

uint32 OpenGLVertexBuffer::GetID()
{
    return vertexBufferID;
}

/////////////////////////////////////////////////////////////////////
// Index Buffer
/////////////////////////////////////////////////////////////////////
OpenGLIndexBuffer::OpenGLIndexBuffer(const void *indices, uint32 size, uint32 count)
{
    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    this->count = count;
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &indexBufferID);
}

void OpenGLIndexBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
}

void OpenGLIndexBuffer::UnBind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32 OpenGLIndexBuffer::GetID()
{
    return indexBufferID;
}

uint32 OpenGLIndexBuffer::GetCount()
{
    return count;
}
