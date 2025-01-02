#ifndef NSL_CHRONO_HPP
#define NSL_CHRONO_HPP

# include <sys/time.h>
# include <NSLplatform.h>

class SimpleChrono
{
public:
	FORCEINLINE
	SimpleChrono(void) = default;

	FORCEINLINE
	void
	SnapStart(void)
	{
		struct timeval	tv;
		gettimeofday(&tv, nullptr);
		timeA = static_cast<double>(tv.tv_sec) * 1000.0 + static_cast<double>(tv.tv_usec) / 1000.0;
	}

	FORCEINLINE
	void
	SnapEnd(void)
	{
		struct timeval	tv;
		gettimeofday(&tv, nullptr);
		timeB = static_cast<double>(tv.tv_sec) * 1000.0 + static_cast<double>(tv.tv_usec) / 1000.0;
		//std::cout << timeB;
	}

	FORCEINLINE
	double
	GetElapsedTime(void)
	{
		return (timeB - timeA);
	}

private:
	double	timeA;
	double	timeB;
};

#endif
