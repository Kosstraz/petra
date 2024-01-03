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
    Handle::currentScene->RemoveObject(this->name);
    this->Free();
}

    /// METHODES

void    PetraO::Destroy() noexcept
{
    this->name = nullptr;
}

void    PetraO::Free() noexcept
{
    this->Destroy();
    delete this->name;
}

    /// STATIQUES