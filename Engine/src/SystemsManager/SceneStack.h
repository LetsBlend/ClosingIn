//
// Created by Let'sBlend on 28/02/2024.
//

#ifndef CLOSING_SCENESTACK_H
#define CLOSING_SCENESTACK_H

class Scene;

class SceneStack
{
public:
    SceneStack() = default;
    ~SceneStack() = default;

    void PushScene(const std::string& name);
    void PopScene(const std::string& name);
    void PopAll();

    Ref<Scene> GetScene(const std::string& name);
    Ref<Scene> GetScene(const int& index);
    bool Exists(const std::string& name);
    void Erase(const std::string& name);

    inline Ref<Scene> front() { return scenePtrs.front(); }
    inline Ref<Scene> back() { return scenePtrs.back(); }
    inline bool empty() { return scenePtrs.empty(); }
    inline int size() { return (int)scenePtrs.size(); }

    inline std::vector<Ref<Scene>>::iterator begin() { return scenePtrs.begin(); }
    inline std::vector<Ref<Scene>>::iterator end() { return scenePtrs.end(); }

private:
    std::vector<Ref<Scene>> scenePtrs;
};


#endif //CLOSING_SCENESTACK_H
