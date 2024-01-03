#ifndef PETRA_SHADERMANAGER_HPP
#define PETRA_SHADERMANAGER_HPP

#include <rendering/Shader.hpp>
#include <core/Scene.hpp>
#include <unordered_map>

struct Handle final
{
        // All Shaders in projects
    static const unsigned char  shadersCount;
    static unsigned int*        shadersProgram;

        // All Scenes
    // The current scene
    inline static Scene*                           currentScene  = nullptr;
    // Holy scenes
    inline static std::unordered_map<const char*, Scene*> scenes = std::unordered_map<const char*, Scene*>();
};

#endif