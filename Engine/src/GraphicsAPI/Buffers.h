//
// Created by Let'sBlend on 15/03/2024.
//

#ifndef CLOSINGIN_BUFFERS_H
#define CLOSINGIN_BUFFERS_H


class VertexBuffer
{
public:
    VertexBuffer() = default;
    virtual ~VertexBuffer() = default;

    static Ref<VertexBuffer> Create(const void* vertices, uint32 size);

    virtual void Bind() = 0;
    virtual void UnBind() = 0;
    virtual uint32 GetID() = 0;
};

class IndexBuffer
{
public:
    IndexBuffer() = default;
    virtual ~IndexBuffer() = default;

    static Ref<IndexBuffer> Create(const void* indices, uint32 size, uint32 count);

    virtual void Bind() = 0;
    virtual void UnBind() = 0;
    virtual uint32 GetID() = 0;
    virtual uint32 GetCount() = 0;
};

#endif //CLOSINGIN_BUFFERS_H
