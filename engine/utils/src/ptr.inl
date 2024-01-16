#include "../ptr.hpp"

template <typename T>
ptr<T>::ptr() noexcept : p(nullptr)
{}

template <typename T>
ptr<T>::ptr(const T& _t) noexcept
{   this->alloc(_t);    }

template <typename T>
ptr<T>::ptr(T* _ptr) noexcept
{
    this->p = new T[1];   
    *this->p = *_ptr;
}

template <typename T>
ptr<T>::~ptr() noexcept
{   this->free();   }   // !'V773 The 'p' pointer was not released in destructor. A memory leak is possible. ptr.inl 18'

template <typename T>
void ptr<T>::re_ptr(T* new_ptr)    noexcept
{
    this->free();
    this->p = new T[1];
    *this->p = *new_ptr;
}

template <typename T>
void ptr<T>::alloc(const T& val)
{   this->p = new T(val);   }

template <typename T>
inline T* ptr<T>::reference()   noexcept
{   return (this->p);   }

template <typename T>
inline void ptr<T>::free()      noexcept
{   
    if (this->p != nullptr)
    {
        delete (this->p);
        this->p = nullptr;
    }
}
