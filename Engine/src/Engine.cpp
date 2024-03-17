//
// Created by Let'sBlend on 27/02/2024.
//

#include "Engine.h"
#include "EngineTime.h"

#include "Events/Event.h"
#include "Events/Input.h"
#include "GLFW/glfw3.h"
#include "Window/Window.h"

#include "SystemsManager/Layer.h"
#include "SystemsManager/LayerStack.h"
#include "SystemsManager/Scene.h"
#include "SystemsManager/SceneStack.h"

#include "GraphicsAPI/GuiHandle.h"
#include "Renderer/Renderer2D/Renderer2D.h"
#include "Renderer/EditorGui.h"
#include "Renderer/ClearRender.h"

Engine::Engine()
{
    s_Instance = this;
}

Engine::~Engine()
{

}

void Engine::Run()
{
    EngineTime engineTime;
    sceneStack = CreateScope<SceneStack>();

    m_Window = CreateRef<Window>("ClosingIn", 1920, 1080);
    m_Renderer = CreateRef<Renderer2D>();
    m_Gui = CreateRef<GuiHandle>();
    m_EditorGui = CreateRef<EditorGui>();
    m_ClearRender = CreateRef<ClearRender>();

    Event::StartUp();
    Input::StartUp(m_Window->GetWindow());

    OnStartUp();
    StartUpScene();

    Event::RegisterEvent(EventType::WindowClose, this, &Engine::CloseApplication);

    while (run)
    {
        engineTime.UpdateStartTime();

        for(const Ref<Layer>& layer : activeScene->layerStack)
            layer->OnUpdate();

        Input::Update();
        engineTime.UpdateEndTime(120);
    }

    Event::UnregisterEvent(EventType::WindowClose, this, &Engine::CloseApplication);

    OnShutDown();
    ShutDownScene();

    Input::ShutDown();
    Event::ShutDown();

    m_Window.reset();
    m_Renderer.reset();
    m_EditorGui.reset();
    m_Gui.reset();
    m_ClearRender.reset();

    sceneStack.reset();
}

void Engine::PushScene(const std::string& scene)
{
// Push Scene:
    if(sceneStack->Exists(scene))
    {
        // TODO: Warn scene already exists. Everything associated to this scene will be overwritten
        sceneStack->Erase(scene);
    }

    sceneStack->PushScene(scene);
    Ref<Scene> scenePtr = sceneStack->GetScene(scene);

// Push Layers:
    // Push all engine layers which shall run before the users
    scenePtr->layerStack.PushEngineLayer(m_Window); // 1st

    // Set where user can push layers
    scenePtr->layerStack.currentUserLayerIndex = 1;

    // Push all engine layers which shall be run after the user layers
    scenePtr->layerStack.PushEngineLayer(m_ClearRender);
    scenePtr->layerStack.PushEngineLayer(m_Renderer);

// Push Overlays:
    // Push all engine overlays which shall run before the users
    //...                                     // 0st

    // Set range where user can push overlays
    scenePtr->layerStack.currentUserOverlayIndex = 0;

    // Push all engine overlays which shall run after the users
    scenePtr->layerStack.PushEngineOverlay(m_EditorGui);
}

void Engine::PopScene(const std::string &scene)
{
    sceneStack->PopScene(scene);
}

void Engine::SwitchScene(const std::string& name)
{
    for(const Ref<Scene>& scene : *sceneStack)
    {
        if(scene->name == name)
            activeScene = scene;
    }

    if(activeScene->layerStack.empty())
        std::cout << "[WARN]: No layer was pushed to active scene!" << std::endl; // TODO: Assertion no layer was pushed
}

void Engine::PushLayer(const std::string& scene, const Ref<Layer>& layer)
{
    Ref<Scene> scenePtr = sceneStack->GetScene(scene);
    scenePtr->layerStack.PushUserLayer(layer);
}

void Engine::PopLayer(const std::string& scene, const Ref<Layer>& layer)
{
    Ref<Scene> scenePtr = sceneStack->GetScene(scene);
    scenePtr->layerStack.PopUserLayer(layer);
}

void Engine::StartUpScene()
{
    if(sceneStack->empty())
        std::cout << "[ERROR]: No scene was pushed!" << std::endl; // We need assertions

    activeScene = sceneStack->front();

    if(activeScene->layerStack.empty())
        std::cout << "[WARNING]: No layer was pushed to active scene!" << std::endl;
}

void Engine::ShutDownScene()
{
    sceneStack->PopAll();
}

void Engine::CloseApplication(Listener& listener)
{
    run = false;
}