#include <core/Core.hpp>

int main()
{
    int errorCode = Core::InitEngine();
    if (errorCode < 0)      return_error("Initialisation du moteur échouée", errorCode)

    Core::CompileAllShaders();

    errorCode = Core::Loop();
    if (errorCode < 0)      return_error("Erreur autour de la lecture de la boucle", errorCode)

    Core::Terminate();
    return (0);
}

// glissement sémentique