#ifndef PETRA_FPSCOUNTER_HPP
#define PETRA_FPSCOUNTER_HPP

#include <core/Time.hpp>

class FPSCounter final
{
public:
    FPSCounter()        noexcept;

    void StartCount()   noexcept
    {
        if (this->fps_time.is_active == 1 && this->fps_time.GetTime() >= 1.0f * 1000.0f)
        {
            printf("%ld\n", this->fps);
            this->fps_time.deltaTime = (1.0 / static_cast<double>(this->fps));
            this->fps = 0;
            this->fps_time.is_active = 0;
        }
        else
            this->fps++;
        if (this->fps_time.is_active == 0)
        {
            this->fps_time.Start();
            this->fps_time.is_active = 1;
        }
    }

    void MarkCount()    noexcept
    {
        this->fps_time.Stop();
    }

    Time     fps_time;
    long int fps;
    double   delta_time;
};

#endif