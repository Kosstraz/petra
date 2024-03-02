#ifndef PETRA_O_HPP
#define PETRA_O_HPP

#include <platforms/macros_platform.h>

//#define ABSTRACT     ((bool8)0)
//#define NON_ABSTRACT ((bool8)1)
//#define ACTOR        ((bool8)1)
//#define IHM          ((bool8)2)
//#define GUI          ((bool8)2)


//template <bool8 abstract_type = ACTOR>
class PetraO
{
public:
        /// CONSTRUCTEURS

     PetraO(const char* name);
     PetraO();
     virtual ~PetraO();

        /// METHODES

        // Supprime l'objet de la scène mais ne le supprime aucunement de la mémoire
    template <class PetraObjectType>
    static PetraObjectType** Creates(const char* common_name, uint64 count)   noexcept;

    virtual void Destroy()       noexcept;

        /// OVERRIDES METHODES
    inline virtual void Build    (uint32 GL_METHOD_DRAW = 0x88E4)           noexcept            {}
    inline virtual void DrawBuild()                                 const   noexcept    FREQ    {}
    inline const  char* GetName()                                   const   noexcept    FREQ    {   return (this->name);    }

        /// STATIQUES
    bool8      isDestroyed;
protected:
    const char*  name;
    
    bool8      neverDestroy;
};

#include <base/src/PetraO.inl>

#endif