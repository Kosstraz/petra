#include <core/Time.hpp>

double Time::deltaTime = 0.0001;

Time::Time() noexcept : is_active(0), time(0)
{
    this->Start();
}

void Time::Start() noexcept
{
    this->begin = std::chrono::high_resolution_clock::now();
}

void Time::Stop() noexcept
{
    this->end  = std::chrono::high_resolution_clock::now();

    this->time = std::chrono::duration_cast<std::chrono::milliseconds>(this->end - this->begin);
}

std::chrono::milliseconds Time::Duration() noexcept
{
    this->time = std::chrono::duration_cast<std::chrono::milliseconds>(this->end - this->begin);
    return time;
}

long long Time::GetTime() const noexcept
{
    return this->time.count();
}