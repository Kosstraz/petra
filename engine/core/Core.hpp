#ifndef PETRA_CORE_HPP
#define PETRA_CORE_HPP

#include <core/Handle.hpp>

#include <glad/glad.h>
#define GLFW_DLL
#include <glfw-3.3.9/glfw3.h>

// Gestion des erreurs + autres utilités
#include <platforms/macros_platform.h>
#include <cstdio>

// Stockages des informations liées aux images, textures
#include <rendering/Texture.hpp>
#include <C/TextureStruct.h>

// Pour la compilation des shaders
#include <rendering/Shader.hpp>

// Calcule des temps d'exécutions
#include <core/Chrono.hpp>

#include <utils/json.hpp>

class Core
{
    /// CONSTRUCTEURS


public:
    /// METHODES

    static int  InitEngine();

    static int  JSONLoader                  (ArrayForJSON* jsonLoaderInfos      );
    static void CompileAllShaders           (const ArrayForJSON& jsonLoaderInfos);
    static void CreateAllImportedTextures   (const ArrayForJSON& jsonLoaderInfos);
    static void FreeJSON                    (ArrayForJSON* jsonLoaderInfos      );

    static void Loop();
};

#endif