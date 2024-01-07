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

    delete (name);
}

// La variable 'name' et sa liste sera delete, la variable 'object' ne sera pas non plus supprimée, sauf sa liste
void Scene::AddObjects(PetraO** objects, const char** name, unsigned short sizeo) noexcept
{
    for (unsigned short i = 0; i < sizeo; i++)
    {
        AddObject(objects[i], name[i]);
        name[i] = nullptr;
        delete name[i];
    }

    *objects = nullptr;
    delete[] objects;
    delete[] name;
}

    // Enlève un objet de la scène.
    // Ne supprime aucunement le pointeur de l'objet.
    // Plus efficace mais ne supprime pas l'objet de la mémoire, chose à faire avant ou après l'utilisation de cette fonction
    // 'Delete' de la mémoire le paramètre 'name' !
void Scene::RemoveObject(const char* name)
{
    std::unordered_map<const char*, PetraO*>::const_iterator ite = this->all_objects_in_scene.find(name);
    if (ite != this->all_objects_in_scene.end())
        this->all_objects_in_scene.erase(name);

    delete (name);
}

    // Enlève un objet de la scène.
    // Supprime l'objet pointeur, de la mémoire, associé au nom.
    // 'Delete' de la mémoire le paramètre 'name' !
void Scene::DeleteObject(const char* name)
{
    std::unordered_map<const char*, PetraO*>::iterator ite = this->all_objects_in_scene.find(name);
    if (ite != this->all_objects_in_scene.end())
    {
        delete (ite->first) ;
        delete (ite->second);
        this->all_objects_in_scene.erase(name);
    }

    delete (name);
}

void Scene::Clear()
{
    this->all_objects_in_scene.clear();
    if (!this->IsEmpty())
        throw (this->all_objects_in_scene);
}

void Scene::LoadThisScene() const noexcept
{
    for (const std::pair<const char*, PetraO*>& objects : this->all_objects_in_scene)
        objects.second->Build(0x88E0); // GL_STREAM_DRAW
}

void Scene::DrawThisScene() const noexcept
{
    for (const std::pair<const char*, PetraO*>& objects : this->all_objects_in_scene)
        objects.second->DrawBuild();
}