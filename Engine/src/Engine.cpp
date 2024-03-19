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

#include "Renderer/Renderer.h"

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
    SceneStack stack;
    sceneStack = &stack;
    m_Window = CreateRef<Window>("ClosingIn", 640, 480);
    m_Renderer = CreateRef<Renderer>();

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
}

void Engine::PushScene(const std::string& scene)
{
    if(sceneStack->Exists(scene))
    {
        // TODO: Warn scene already exists. Everything associated to this scene will be overwritten
        sceneStack->Erase(scene);
    }

    sceneStack->PushScene(scene);
    Ref<Scene> scenePtr = sceneStack->GetScene(scene);
    // Push all engine layers which shall be run before the user layers
    scenePtr->layerStack.PushLayer(m_Window); // 1st

    scenePtr->layerStack.userLayerStartIndex = 1;
    scenePtr->layerStack.userLayerEndIndex = scenePtr->layerStack.userLayerStartIndex;

    // Push all engine layers which shall be run after the user layers
    scenePtr->layerStack.PushLayer(m_Renderer);
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