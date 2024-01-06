#include <core/Scene.hpp>

template <class PetraObjectType>
PetraObjectType* Scene::FindACTOR(const char* name) const
{
    std::unordered_map<const char*, PetraO*>::const_iterator ite = this->all_objects_in_scene.find(name);
    if (ite != this->all_objects_in_scene.end())
        return (reinterpret_cast<PetraObjectType*>(ite->second));
        
    return (nullptr);
}