#ifndef PETRA_SCENE_HPP
#define PETRA_SCENE_HPP

#include <base/PetraO.hpp>
#include <utils/ptr.hpp>
#include <unordered_map>

class Scene
{
public:
        // CONSTRUCTEURS

    Scene() = default;
    ~Scene();

        // METHODES

    void AddObject (PetraO* object, const char* name)  noexcept;
    void AddObjects(PetraO** objects, const char** name, uint32 sizeo) noexcept;
    void RemoveObject_deprecated(const char* name);
    void DeleteObject(const char* name);

    template <class PetraObjectType>
    ptr<PetraObjectType> FindACTOR(const char* name) const;

    void Clear     ();

    void LoadThisScene() const noexcept;
    void DrawThisScene() const noexcept;

    inline boolean IsEmpty() const noexcept
    {return (this->all_objects_in_scene.empty());};

protected:
        // ATTRIBUTS

    std::unordered_map<const char*, ptr<PetraO>> all_objects_in_scene = std::unordered_map<const char*, ptr<PetraO>>();
};

#include "src/Scene.inl"

#endif