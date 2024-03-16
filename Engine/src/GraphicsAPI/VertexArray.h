//
// Created by Let'sBlend on 15/03/2024.
//

#ifndef CLOSINGIN_VERTEXARRAY_H
#define CLOSINGIN_VERTEXARRAY_H

class VertexArray
{
public:
    VertexArray() = default;
    virtual ~VertexArray() = default;

    static Ref<VertexArray> Create();

    virtual void SetLayout() = 0;
    virtual void Bind() = 0;
    virtual void UnBind() = 0;
    virtual uint32 GetID() = 0;
};


#endif //CLOSINGIN_VERTEXARRAY_H
