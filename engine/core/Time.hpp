#ifndef PETRA_TIME_HPP
#define PETRA_TIME_HPP

#include <cstdio>
#include <chrono>

class Time final
{
public:
    Time() noexcept;
   ~Time() noexcept = default;

    void Start() noexcept;
    void Stop () noexcept;

    std::chrono::milliseconds Duration() noexcept;
    long long GetTime()            const noexcept;

    bool is_active;

    static double deltaTime;

private:
    std::chrono::high_resolution_clock::time_point begin;
    std::chrono::high_resolution_clock::time_point end  ;

    std::chrono::milliseconds time;
};

#endif