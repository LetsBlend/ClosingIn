//
// Created by Let'sBlend on 12/03/2024.
//

#ifndef CLOSINGIN_OPENGLBUFFERS_H
#define CLOSINGIN_OPENGLBUFFERS_H

#include "GraphicsAPI/Buffers.h"

class OpenGLVertexBuffer : public VertexBuffer
{
public:
    OpenGLVertexBuffer(const void* vertices, uint32 size);
    ~OpenGLVertexBuffer() override;

    void Bind() override;
    void UnBind() override;
    uint32 GetID() override;

private:
    uint32 vertexBufferID;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:
    OpenGLIndexBuffer(const void* indices, uint32 size, uint32 count);
    ~OpenGLIndexBuffer() override;

    void Bind() override;
    void UnBind() override;
    uint32 GetID() override;
    uint32 GetCount() override;

private:
    uint32 indexBufferID;
    uint32 count;
};

// TODO: More Buffer type options...

#endif //CLOSINGIN_OPENGLBUFFERS_H
