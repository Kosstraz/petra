#ifndef PTR_HPP
#define PTR_HPP

#include "platforms/opti_macros.hpp"
#include <memory>

template <typename T>
class ptr final
{
public:
        // CONSTRUCTEURS

    ptr()               noexcept;
    ptr(const T& _t)    noexcept;
    ptr(T* _ptr)  noexcept;
   ~ptr()               noexcept;

        // METHODES

    void        alloc (const T& val = static_cast<T>(0));
    void        re_ptr(T* new_ptr)                          noexcept    RARELY;
    inline void free()                                      noexcept;
    inline T*   reference()                                 noexcept;

    inline static constexpr ptr<T> null()                   noexcept
    {   return (ptr<T>());  }

    template <typename To>
    inline ptr<To> cast_ptr()                               noexcept
    {
        ptr<To> ret;
        ret.p = reinterpret_cast<To*>(this->p);
        return (ret);
    }

        // OPERATEURS

    inline ptr<T> operator=(T _t)                           noexcept    FREQ
    {   *this->p = _t;  return (*this);  }

    inline const boolean operator==(ptr<T> other)   const   noexcept    FREQ
    {
        if (*(this->p) == *other)   return (0x01);      // true
        else    return (0x00);                          // false
    }

    inline const boolean operator!=(ptr<T> other)   const   noexcept    FREQ
    {   return !(*this == other);   }

    inline T* operator&()                                   noexcept    FREQ    // const
    {   return (this->reference()); } 

    inline T& operator*()                                   noexcept    FREQ    // const
    {   return (*this->p);  }

    inline T* operator->()                                              FREQ // const
    {   if (this->p == nullptr)
            throw std::runtime_error("Attempted to access null pointer in 'operator->' with ptr<T>.");
        else
            return (this->p);   }

        // VARIABLES

    T* p;
};

#include "src/ptr.inl"

#endif