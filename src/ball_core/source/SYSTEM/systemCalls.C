//_new_file_header


#include <BALL/core/system/systemCalls.h>

#ifdef BALL_OS_WINDOWS
#include <windows.h>
#else
#ifdef BALL_HAS_UNISTD_H
#include <unistd.h>
#endif
#endif


namespace BALL
{
	void sleepFor(Size mseconds)
	{
#ifdef BALL_OS_WINDOWS
 		Sleep(mseconds);
#else
		usleep(mseconds);
#endif
	}
} // namespace BALL

