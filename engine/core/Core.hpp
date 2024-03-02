#ifndef PETRA_CORE_HPP
#define PETRA_CORE_HPP

    // Inclusion des DLL si besoin
    // Détection du système d'exploitation
    // Gérer les nécessités
#include <platforms/setup.h>

    // Contexte OpenGL et gérence des fenêtres
#include <glad/glad.h>
// !#define GLFW_DLL
#include <glfw-3.3.9/glfw3.h>

    // Les resources globales du moteur
#include <core/Handle.hpp>

    // Utilités et MACRO portables
#include <platforms/macros_platform.h>
#include <cstdio>

    // Stockages des informations liées aux images, les textures
#include <rendering/Texture.hpp>

    // Pour la compilation des shaders
#include <rendering/Shader.hpp>

    // Calcule des temps d'exécutions
#include <core/Time.hpp>

    // Parser et ouvrir les fichiers .json compatibles avec Petra
#include <utils/json.hpp>

class Core final
{
public:
    /// METHODES

    static int  InitEngine();

    static int  JSONLoader                  (ArrayForJSON* jsonLoaderInfos      );
    static int  CompileAllShaders           (const ArrayForJSON& jsonLoaderInfos);
    static void CreateAllImportedTextures   (const ArrayForJSON& jsonLoaderInfos);
    static void FreeJSON                    (ArrayForJSON* jsonLoaderInfos      );

    static int  Loop();
};

#endif