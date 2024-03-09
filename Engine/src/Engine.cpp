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

    Window window;
    window.StartUp("ClosingIn", 640, 480);

    Event::StartUp();
    Input::StartUp(window.GetWindow());

    sceneStack = new SceneStack;

    OnStartUp();
    StartUpScene();

    Event::RegisterEvent(EventType::WindowClose, this, &Engine::CloseApplication);
    Event::RegisterEvent(EventType::TextInput, this, &Engine::Test);

    std::thread myThread(Event::FireEvent, &run);

    while (run)
    {
        engineTime.UpdateStartTime();
        window.UpdateEvents();

        //glClearColor(1, 0, 1, 1);
        //glClear(GL_COLOR_BUFFER_BIT);

        window.Update();
        for(Layer* layer : activeScene->layerStack)
            layer->OnUpdate();

        Input::Update();
        engineTime.UpdateEndTime(120);
    }

    myThread.join();

    Event::UnregisterEvent(EventType::WindowClose, this, &Engine::CloseApplication);
    Event::UnregisterEvent(EventType::TextInput, this, &Engine::Test);

    OnShutDown();
    ShutDownScene();

    delete sceneStack;

    Input::ShutDown();
    Event::ShutDown();

    window.ShutDown();
}

void Engine::PushScene(std::string&& name)
{
    sceneStack->PushScene(std::move(name));
}

void Engine::PopScene(std::string&& name)
{
    sceneStack->PopScene(std::move(name));
}

void Engine::SwitchScene(const std::string& name)
{
    for(const std::shared_ptr<Scene>& scene : *sceneStack)
    {
        if(scene->name == name)
            activeScene = scene;
    }

    if(activeScene->layerStack.empty())
        std::cout << "[WARN]: No layer was pushed to active scene!" << std::endl;
}

void Engine::PushLayer(std::string&& scene, Layer *layer)
{
    std::shared_ptr<Scene> getScene = sceneStack->GetScene(std::move(scene));
    getScene->layerStack.PushLayer(layer);
}

void Engine::PopLayer(std::string&& scene, Layer *layer)
{
    std::shared_ptr<Scene> getScene = sceneStack->GetScene(std::move(scene));
    getScene->layerStack.PopLayer(layer);
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

void Engine::Test(Listener& listener)
{
    std::cout << listener.metaData.uint8 << std::endl;
}
