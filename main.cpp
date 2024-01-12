#include <core/Core.hpp>

int main()
{
        // Initialisation du moteur
    int errorCode = Core::InitEngine();
    if (errorCode < 0)      return_error("Initialisation du moteur échouée", errorCode)

        // Charge les informations contenus dans le JSON "to_load.json" et les utilise pas la suite
    ArrayForJSON jsonLoader = ArrayForJSON();
    if (Core::JSONLoader(&jsonLoader) < 0)
        return JSON_BAD_OPENNING;
        
    Core::CompileAllShaders         (jsonLoader );
    //Core::CreateAllImportedTextures (jsonLoader );
    Core::FreeJSON                  (&jsonLoader);

        // Boucle principale
    Core::Loop();

    return (0);
}

// glissement sémentique