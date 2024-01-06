#include <core/Chrono.hpp>

Chrono::Chrono() noexcept : time(0)
{
    this->Start();
}

Chrono::~Chrono() noexcept
{}

void Chrono::Start() noexcept
{
    this->begin = std::chrono::high_resolution_clock::now();
}

void Chrono::Stop() noexcept
{
    this->end  = std::chrono::high_resolution_clock::now();

    this->time = std::chrono::duration_cast<std::chrono::milliseconds>(this->end - this->begin);
}

std::chrono::milliseconds Chrono::Duration() noexcept
{
    this->time = std::chrono::duration_cast<std::chrono::milliseconds>(this->end - this->begin);
    return time;
}

long long Chrono::GetTime() const noexcept
{
    return this->time.count();
}