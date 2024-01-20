#include <base/PetraO.hpp>

#include <core/Handle.hpp>

    /// CONSTRUCTEURS

PetraO::PetraO(const char* name) : isDestroyed((boolean)0x00), name(name), neverDestroy((boolean)0x00)
{   Handle::currentScene->AddObject(this, this->name);  }

PetraO::~PetraO()
{
    this->Destroy();      // !'V1053 Calling the 'Destroy' virtual function in the destructor may lead to unexpected result at runtime. PetraO.cpp 15'
}

    /// METHODES

void    PetraO::Destroy() noexcept
{
    if (Handle::currentScene->FindACTOR<PetraO>(this->name) != nullptr)
        Handle::currentScene->DeleteObject(this->name);
}

    /// STATIQUES