#include <core/Scene.hpp>

    // CONSTRUCTEURS

Scene::~Scene()
{
    //this->Clear();
}

    // METHODES

// Ne supprime rien de la mémoire
void Scene::AddObject(PetraO* object, const char* name) noexcept
{
    //this->all_objects_in_scene.insert(std::pair<const char*, PetraO*>(name, object));  // insert() || emplace() || try_emplace()
}

// Ne supprime rien de la mémoire
void Scene::AddObjects(PetraO** objects, const char** name, uint32 sizeo) noexcept
{
    //for (uint32 i = 0; i < sizeo; i++)
    //    AddObject(&(objects[i]), name[i]);
}

    // Enlève un objet de la scène.
    // Supprime l'objet pointeur, de la mémoire, associé au nom.
    // 'Delete' de la mémoire le paramètre 'name' !
void Scene::DeleteObject(const char* name)
{
    std::unordered_map<const char*, PetraO*>::iterator ite = this->all_objects_in_scene.find(name);
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
        throw std::runtime_error("La scène n'a pas été vidée correctement.");
}

void Scene::LoadThisScene() noexcept
{
    for (   std::unordered_map<const char*, PetraO*>::iterator i = this->all_objects_in_scene.begin();
            i != this->all_objects_in_scene.end();
            ++i)
        i->second->Build(0x88E0);
}

void Scene::DrawThisScene() noexcept
{
    for (   std::unordered_map<const char*, PetraO*>::iterator i = this->all_objects_in_scene.begin();
            i != this->all_objects_in_scene.end();
            ++i)
        i->second->DrawBuild();
}