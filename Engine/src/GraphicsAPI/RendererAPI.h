//
// Created by Let'sBlend on 15/03/2024.
//

#ifndef CLOSINGIN_RENDERERAPI_H
#define CLOSINGIN_RENDERERAPI_H


class RendererAPI
{
public:
    RendererAPI() = default;
    virtual ~RendererAPI() = default;

    enum class API
    {
        None,
        OpenGL
    };

    static void GSetFlags();
    static void GSetViewport(uint16 posX, uint16 posY, uint16 width, uint16 height);
    static void GDrawIndexed(uint32 indexCount);
    static void GClearColor(const Math::vec4& color);
    static void GClear();
    inline static API GetAPI() { return s_API; };

private:
    virtual void SetFlags() = 0;
    virtual void SetViewport(uint16 posX, uint16 posY, uint16 width, uint16 height) = 0;
    virtual void DrawIndexed(uint32 indexCount) = 0;
    virtual void ClearColor(const Math::vec4& color) = 0;
    virtual void Clear() = 0;

private:
    static Scope<RendererAPI> Create();
    inline static Scope<RendererAPI> s_rendererApi = RendererAPI::Create();

    inline static API s_API = API::OpenGL;
};


#endif //CLOSINGIN_RENDERERAPI_H