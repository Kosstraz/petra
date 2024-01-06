#ifndef PETRA_CHRONO_HPP
#define PETRA_CHRONO_HPP

#include <cstdio>
#include <chrono>

class Chrono final
{
public:
    Chrono() noexcept;
   ~Chrono() noexcept;

    void Start() noexcept;
    void Stop () noexcept;

    std::chrono::milliseconds Duration() noexcept;
    long long GetTime()            const noexcept;

private:
    std::chrono::high_resolution_clock::time_point begin;
    std::chrono::high_resolution_clock::time_point end  ;

    std::chrono::milliseconds time;
};

#endif