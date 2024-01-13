#include <base/PetraO.hpp>

#include <core/Handle.hpp>
#include <utils/ptr.hpp>

    /// CONSTRUCTEURS

PetraO::PetraO(const char* name) : isDestroyed(false)
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
    this->isDestroyed = true;
    Handle::currentScene->DeleteObject(this->name);
}

    /// STATIQUES