#include <core/Scene.hpp>

    // CONSTRUCTEURS

Scene::~Scene()
{
    this->Clear();
}

    // METHODES

// Ne supprime rien de la mémoire
void Scene::AddObject(PetraO* object, const char* name) noexcept
{
    this->all_objects_in_scene.insert(std::pair<const char*, ptr<PetraO>>(name, ptr<PetraO>(object)));
}

// Ne supprime rien de la mémoire
void Scene::AddObjects(PetraO** objects, const char** name, uint32 sizeo) noexcept
{
    for (uint32 i = 0; i < sizeo; i++)
        AddObject(objects[i], name[i]);
}

    // Enlève un objet de la scène.
    // Supprime l'objet pointeur, de la mémoire, associé au nom.
    // 'Delete' de la mémoire le paramètre 'name' !
void Scene::DeleteObject(const char* name)
{
    std::unordered_map<const char*, ptr<PetraO>>::iterator ite = this->all_objects_in_scene.find(name);
    if (ite != this->all_objects_in_scene.end())
    {
        //ite->second.free();
        this->all_objects_in_scene.erase(name);
    }
}

void Scene::Clear()
{
    this->all_objects_in_scene.clear();
    if (!this->IsEmpty())
        throw (this->all_objects_in_scene);
}

void Scene::LoadThisScene() const noexcept
{
    for (const std::pair<const char*, ptr<PetraO>>& objects : this->all_objects_in_scene)
        objects.second->Build(0x88E0); // GL_STREAM_DRAW
}

void Scene::DrawThisScene() const noexcept
{
    for (const std::pair<const char*, ptr<PetraO>>& objects : this->all_objects_in_scene)
        objects.second->DrawBuild();
}