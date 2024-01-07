#ifndef PETRA_HANDLE_HPP
#define PETRA_HANDLE_HPP

#include <C/Coords.h>
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

        // The window screen
    inline static struct CoordsI window_size = {800, 600};

        // The used camera
    //inline static Camera* camera = nullptr;
};

#endif