//
// Created by Let'sBlend on 27/02/2024.
//

#ifndef APPLICATION_ENGINE_H
#define APPLICATION_ENGINE_H

class Listener;

class SceneStack;
class Scene;
class Layer;

class Window;
class Renderer2D;

class Engine
{
public:
    virtual ~Engine();

    virtual void OnStartUp() {};
    virtual void OnShutDown() {};

    void Run();

    static void PushScene(const std::string& scene);
    static void PopScene(const std::string& scene);
    static void SwitchScene(const std::string& name);

    // Pushes a layer and calls the OnAttach function on the layer.
    static void PushLayer(const std::string& scene, const Ref<Layer>& layer);
    // Pops a layer and calls the OnDetach function from the layer.
    static void PopLayer(const std::string& scene, const Ref<Layer>& layer);
protected:
    Engine();

private:
    void CloseApplication(Listener& listener);

    void StartUpScene();
    void ShutDownScene();

    inline static Ref<Scene> activeScene = nullptr;
    inline static SceneStack* sceneStack;

    inline static bool run = true;

    inline static Ref<Window> m_Window;
    inline static Ref<Renderer2D> m_Renderer;
    inline static Engine* s_Instance = nullptr;
};


#endif //APPLICATION_ENGINE_H
