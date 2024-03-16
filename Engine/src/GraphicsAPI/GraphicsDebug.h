//
// Created by Let'sBlend on 15/03/2024.
//

#ifndef CLOSINGIN_GRAPHICSDEBUG_H
#define CLOSINGIN_GRAPHICSDEBUG_H


class GraphicsDebug
{
public:
    GraphicsDebug() = default;
    virtual ~GraphicsDebug() = default;

    static void GSetDebugFlags();
    static void GEnableDebug();

private:

    virtual void SetDebugFlag() = 0;
    virtual void EnableDebug() = 0;

    static Scope<GraphicsDebug> Create();
    inline static Scope<GraphicsDebug> graphicsDebug = GraphicsDebug::Create();
};


#endif //CLOSINGIN_GRAPHICSDEBUG_H
