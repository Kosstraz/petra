#include <core/SceneManager.hpp>

void SceneManager::LoadScene(const char* name)
{
    std::unordered_map<const char*, Scene*>::const_iterator ite = Handle::scenes.find(name);
    if (ite == Handle::scenes.end())
    {
        DEBUG(SCENE_LOG, "Aucune scène trouvée");
        throw ("Aucune scène trouvée");
    }
    else
        Handle::currentScene = ite->second;

    delete name;
}

void SceneManager::SetCurrentScene(Scene* scene)
{
    Handle::currentScene = scene;
}

Scene* SceneManager::GetCurrentScene() noexcept
{
    return Handle::currentScene;
}