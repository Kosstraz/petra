#include <core/Scene.hpp>

template <class PetraObjectType>
ptr<PetraObjectType> Scene::FindACTOR(const char* name) const
{
    std::unordered_map<const char*, ptr<PetraO>>::const_iterator ite = this->all_objects_in_scene.find(name);
    if (ite != this->all_objects_in_scene.end())
        return (ite->second.cast_ptr<PetraObjectType>());
        
    return (ptr<PetraObjectType>::null());
}