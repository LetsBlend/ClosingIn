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

#include "GraphicsAPI/Gui/GuiHandle.h"
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
    scenePtr->layerStack.PushLayer(m_Window); // 1st

    // Set range where user can push layers
    scenePtr->layerStack.userLayerStartIndex = 1;
    scenePtr->layerStack.userLayerEndIndex = scenePtr->layerStack.userLayerStartIndex;
    // Reset currentLayerIndex since its dependent on userLayerStartIndex
    scenePtr->layerStack.currentLayerIndex = 0;

    // Push all engine layers which shall be run after the user layers
    scenePtr->layerStack.PushLayer(m_ClearRender);
    scenePtr->layerStack.PushLayer(m_Renderer);

// Push Overlays:
    // Push all engine overlays which shall run before the users
    //...                                     // 0st

    // Set range where user can push overlays
    scenePtr->layerStack.userOverlayStartIndex = 0;
    scenePtr->layerStack.userOverlayEndIndex = scenePtr->layerStack.userOverlayStartIndex;
    // Reset currentOverlayIndex since its dependent on userOverlayStartIndex
    scenePtr->layerStack.currentOverlayIndex = 0;

    // Push all engine overlays which shall run after the users
    scenePtr->layerStack.PushOverlay(m_EditorGui);
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
    scenePtr->layerStack.PushLayer(layer);
    scenePtr->layerStack.userLayerEndIndex++;
}

void Engine::PopLayer(const std::string& scene, const Ref<Layer>& layer)
{
    Ref<Scene> scenePtr = sceneStack->GetScene(scene);
    scenePtr->layerStack.PopLayer(layer);
    scenePtr->layerStack.userLayerEndIndex--;
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