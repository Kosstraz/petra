#ifndef PETRA_CORE_HPP
#define PETRA_CORE_HPP

#include <core/Handle.hpp>

//#include "Graphic/Graphic.hpp"

#include <glad/glad.h>
#define GLFW_DLL
#include <glfw-3.3.9/glfw3.h>

#include <platforms/macros_platform.h>
#include <cstdio>

//includes de test
#include <rendering/Shader.hpp>

class Core
{
    /// CONSTRUCTEURS


public:
    /// METHODES

    static int  InitEngine();

    static void CompileAllShaders();

    static void Loop();

    static void Terminate();

    /// VARIABLES
};

#endif