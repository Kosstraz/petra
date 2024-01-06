#include <core/Core.hpp>

int main()
{
    int initLog = Core::InitEngine();
    if (initLog < 0)      return (initLog);

    Core::CompileAllShaders();

    Core::Loop();

    Core::Terminate();
    return (0);
}

// glissement sémentique