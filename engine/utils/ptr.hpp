#ifndef PTR_HPP
#define PTR_HPP

#include "../platforms/opti_macros.hpp"
#include <memory>

template <typename T>
class ptr final
{
public:
        // CONSTRUCTEURS

    ptr()       noexcept;
    ptr(const T& _t)   noexcept;
   ~ptr()       noexcept;

        // METHODES

    void        re_ptr(T* new_ptr)                          noexcept      RARELY;
    void        alloc (const T& val = static_cast<T>(0))    noexcept;
    inline void free()                                      noexcept;
    inline T*   reference()                         const   noexcept;

    inline static constexpr ptr<T> null()                   noexcept
    {   return (ptr<T>());  }

    template <typename To>
    inline ptr<To> cast_ptr()       const   noexcept
    {
        ptr<To> ret;
        ret.p = reinterpret_cast<To*>(this->p);
        return (ret);
    }

        // OPERATEURS

    inline ptr<T> operator=(T _t)           noexcept    FREQ
    {   return (ptr(_t));  }

    inline T* operator&()           const   noexcept    FREQ
    {   return (this->reference()); } 

    inline const T& operator*()     const   noexcept    FREQ
    {   return (*this->p);  }

    inline T* operator->()          const               FREQ
    {   if (this->p == nullptr)
            throw std::runtime_error("Attempted to access null pointer");
        else
            return (this->p);   }

        // VARIABLES

    T* p;
};

#include "src/ptr.inl"

#endif