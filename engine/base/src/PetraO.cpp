#include <base/PetraO.hpp>

#include <core/Handle.hpp>

    /// CONSTRUCTEURS

PetraO::PetraO(const char* name)
{
    this->name = nullptr;
    this->name = name;

    Handle::currentScene->AddObject(this, name);
}

PetraO::~PetraO()
{
    this->Destroy();
}

    /// METHODES

void    PetraO::Destroy() noexcept
{
    Handle::currentScene->RemoveObject(this->name);
}

    /// STATIQUES