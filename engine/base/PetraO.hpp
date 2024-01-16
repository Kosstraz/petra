#ifndef PETRA_O_HPP
#define PETRA_O_HPP

#include <platforms/macros_platform.h>

//#define ABSTRACT     ((boolean)0)
//#define NON_ABSTRACT ((boolean)1)
//#define ACTOR        ((boolean)1)
//#define IHM          ((boolean)2)
//#define GUI          ((boolean)2)


//template <boolean abstract_type = ACTOR>
class PetraO
{
public:
        /// CONSTRUCTEURS

     PetraO(const char* name);
     PetraO();
     virtual ~PetraO();

        /// METHODES

        // Supprime l'objet de la scène mais ne le supprime aucunement de la mémoire
    virtual void Destroy()       noexcept;

        /// OVERRIDES METHODES
    inline virtual void Build    (uint32 GL_METHOD_DRAW = 0x88E4)           noexcept            {}
    inline virtual void DrawBuild()                                 const   noexcept    FREQ    {}
    inline const  char* GetName()                                   const   noexcept    FREQ    {   return (this->name);    }

        /// STATIQUES
    boolean      isDestroyed;
protected:
    const char*  name;
    
    boolean      neverDestroy;
};

//#include <base/src/PetraO.inl>

#endif