//
// Created by Let'sBlend on 12/03/2024.
//

#ifndef CLOSINGIN_OPENGLVERTEXARRAY_H
#define CLOSINGIN_OPENGLVERTEXARRAY_H

#include "GraphicsAPI/VertexArray.h"

class OpenGLVertexArray : public VertexArray
{
public:
    OpenGLVertexArray();
    ~OpenGLVertexArray() override;

    void SetLayout() override;

    void Bind() override;
    void UnBind() override;
    uint32 GetID() override;

private:
    uint32 vertexArrayID;
};


#endif //CLOSINGIN_OPENGLVERTEXARRAY_H
