#include "../ptr.hpp"

template <typename T>
ptr<T>::ptr() noexcept : p(nullptr)
{}

template <typename T>
ptr<T>::ptr(const T& _t) noexcept
{   this->alloc(_t);    }

template <typename T>
ptr<T>::~ptr() noexcept
{   //this->free();   }
}
template <typename T>
void ptr<T>::re_ptr(T* new_ptr)    noexcept
{   this->p = new_ptr;  }

template <typename T>
void ptr<T>::alloc(const T& val)    noexcept
{   this->p = new T(val);   }

template <typename T>
inline T* ptr<T>::reference()    const  noexcept
{   return (this->p);   }

template <typename T>
inline void ptr<T>::free()    noexcept
{   delete (this->p);  }
