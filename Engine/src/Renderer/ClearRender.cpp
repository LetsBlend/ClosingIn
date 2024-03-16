//
// Created by Let'sBlend on 16/03/2024.
//

#include "ClearRender.h"
#include "GraphicsAPI/RendererAPI.h"

void ClearRender::OnAttach()
{
    Layer::OnAttach();
}

void ClearRender::OnDetach()
{
    Layer::OnDetach();
}

void ClearRender::OnUpdate()
{
    RendererAPI::GClearColor(Math::vec4(.6f, .6f, .8f, 1));
    RendererAPI::GClear();
}
