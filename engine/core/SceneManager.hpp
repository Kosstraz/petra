#ifndef PETRA_SCENEMANAGER_HPP
#define PETRA_SCENEMANAGER_HPP

#include <core/Handle.hpp>
#include <core/Scene.hpp>

class SceneManager final : public Scene
{
public:
    static void LoadScene(const char* sceneName);
    static void SetCurrentScene(Scene* scene);

    static Scene* GetCurrentScene() noexcept;

private:
};

#endif