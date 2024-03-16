//
// Created by Let'sBlend on 11/03/2024.
//

#include "Renderer2D.h"
#include "Events/Event.h"

void Renderer2D::OnAttach()
{
    //glAPI.SetFlags();
    Event::RegisterEvent(EventType::WindowResize, this, &Renderer2D::OnWindowResize);

    vA->Bind();

    vB->Bind();
    iB->Bind();

    vA->SetLayout();
    vA->UnBind();

    sh->SetInt(0, "ourTexture");
    sh->SetInt(1, "otherTexture");
}

void Renderer2D::OnDetach()
{
    Event::UnregisterEvent(EventType::WindowResize, this, &Renderer2D::OnWindowResize);
}

void Renderer2D::OnUpdate()
{
    glAPI->ClearColor(Math::vec4(.6f, .6f, .8f, 1));
    glAPI->Clear();

    // Scene Rendering
    // Temporary
    sh->Bind();
    vA->Bind();
    t02D->Bind(1);
    t12D->Bind(0);
    glAPI->DrawIndexed(iB->GetCount());
    t12D->UnBind(0);
    t02D->UnBind(1);
    vA->UnBind();
    sh->UnBind();
    // Scene Debug Rendering

    // UI Rendering

    // UI Debug Rendering
}

void Renderer2D::OnWindowResize(Listener& listener)
{
    std::cout << "Window resized " << listener.metaData.ui16[0] << " " << listener.metaData.ui16[1] << std::endl;
    glAPI->SetViewport(0, 0, listener.metaData.ui16[0], listener.metaData.ui16[1]);
}
