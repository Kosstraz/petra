#include <core/Core.hpp>

int main()
{
        // Initialisation du moteur
    int errorCode = Core::InitEngine();
    if (errorCode < 0)      return_error("Initialisation du moteur échouée", errorCode)

        // Charge les informations contenus dans le JSON "to_load.json" et les utilise par la suite
    ArrayForJSON jsonLoader = ArrayForJSON();
    if ((errorCode = Core::JSONLoader(&jsonLoader)) < 0)
        return_error("Erreur lors de la récupération des informations du fichier 'to_load.json'", errorCode);
    if ((errorCode = Core::CompileAllShaders(jsonLoader)) < 0)
        return_error("Erreur lors de la compilation des shaders", errorCode);
    Core::FreeJSON(&jsonLoader);

        // Boucle principale
    return (Core::Loop());
}

// glissement sémentique