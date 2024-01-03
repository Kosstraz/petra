#include <core/Scene.hpp>

    // CONSTRUCTEURS

Scene::~Scene()
{
    this->Clear();
}

    // METHODES

// La variable 'name' sera delete mais pas la variable object
void Scene::AddObject(PetraO* object, const char* name) noexcept
{
    this->all_objects_in_scene.insert(std::pair<const char*, PetraO*>(name, object));
    delete name;
}

// La variable 'name' et sa liste sera delete, la variable 'object' ne sera pas non plus supprimée, sauf sa liste
void Scene::AddObjects(PetraO** objects, const char** name, unsigned short sizeo) noexcept
{
    for (unsigned short i = 0; i < sizeo; i++)
    {
        AddObject(objects[i], name[i]);
        delete name[i];
    }

    delete[] objects;
    delete[] name;
}

PetraO* Scene::FindACTOR(const char* name)
{
    std::unordered_map<const char*, PetraO*>::const_iterator ite = this->all_objects_in_scene.find(name);
    if (ite != this->all_objects_in_scene.end())
        return (ite->second);
    return (nullptr);
}

void Scene::RemoveObject(const char* name)
{
    std::unordered_map<const char*, PetraO*>::const_iterator ite = this->all_objects_in_scene.find(name);
    if (ite != this->all_objects_in_scene.end())
        this->all_objects_in_scene.erase(name);
}

void Scene::Clear()
{
    this->all_objects_in_scene.clear();
    if (!this->IsEmpty())
        throw ("Scene clear doesn't work :/");
}

void Scene::LoadThisScene() const noexcept
{
    for (const std::pair<const char*, PetraO*>& objects : this->all_objects_in_scene)
        objects.second->Build(0x88E8); // GL_DYNAMIC_DRAW
}

void Scene::DrawThisScene() const noexcept
{
    for (const std::pair<const char*, PetraO*>& objects : this->all_objects_in_scene)
        objects.second->DrawBuild();
}