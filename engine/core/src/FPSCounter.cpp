#include <core/FPSCounter.hpp>

FPSCounter::FPSCounter() noexcept : fps_time(Time()), fps(0), delta_time(0)
{
    this->fps_time.Start();
}