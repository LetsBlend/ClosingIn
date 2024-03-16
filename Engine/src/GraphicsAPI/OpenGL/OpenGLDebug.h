//
// Created by Let'sBlend on 14/03/2024.
//

#ifndef CLOSINGIN_OPENGLDEBUG_H
#define CLOSINGIN_OPENGLDEBUG_H

#include "GraphicsAPI/GraphicsDebug.h"

typedef unsigned int GLenum;
typedef int GLsizei;

class OpenGLDebug : public GraphicsDebug
{
public:
    OpenGLDebug() = default;
    ~OpenGLDebug() override = default;

    void SetDebugFlag() override;
    void EnableDebug() override;

private:
    static void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam);
};


#endif //CLOSINGIN_OPENGLDEBUG_H
