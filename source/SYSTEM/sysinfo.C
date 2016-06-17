// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// $Id: sysinfo.C,v 1.22 2005/12/23 17:03:06 amoll Exp $

#include <BALL/SYSTEM/sysinfo.h>

#ifdef BALL_HAS_SYS_SYSINFO_H
#	 include <sys/sysinfo.h>
#	 include <BALL/SYSTEM/file.h>
#else
# ifdef BALL_COMPILER_MSVC
#	  define WIN32_LEAN_AND_MEAN
#	  include <windows.h>
# endif
# ifdef BALL_OS_DARWIN
#   include <cstdlib>
#		include <sys/sysctl.h>
#   include <mach/mach.h>
# endif
#endif

namespace BALL
{
	namespace SysInfo
	{

#if defined(BALL_OS_LINUX) && defined(BALL_HAS_SYS_SYSINFO_H)

		LongIndex getAvailableMemory()
		{
			LongIndex mem = getFreeMemory();
			return mem;
		}

		LongIndex getFreeMemory()
		{
			struct sysinfo info;
			LongIndex result = sysinfo(&info);
			if (result == -1) 
			{
				return result;
			}
			return info.freeram * info.mem_unit;
		}

		LongIndex getTotalMemory()
		{
			struct sysinfo info;
			LongIndex result = sysinfo(&info);
			if (result == -1) 
			{
				return result;
			}
			return info.totalram * info.mem_unit;
		}

		LongIndex getBufferedMemory()
		{
			struct sysinfo info;
			LongIndex result = sysinfo(&info);
			if (result == -1) return result;
			return info.bufferram * info.mem_unit;
		}

		Time getUptime()
		{
			struct sysinfo info;
			LongIndex result = sysinfo(&info);
			if (result == -1) return result;
			return info.uptime;
		}

		Index getNumberOfProcessors()
		{
			return get_nprocs();
		}


		LongIndex getFreeSwapSpace()
		{
			struct sysinfo info;
			LongIndex result = sysinfo(&info);
			if (result == -1) return result;
			return info.freeswap * info.mem_unit;
		}
#else
#ifdef BALL_COMPILER_MSVC

		/// internal helper method used on Windows Platform, not available extern!
		MEMORYSTATUSEX getMemoryStatus()
		{
			MEMORYSTATUSEX statex;
			statex.dwLength = sizeof (statex);
			GlobalMemoryStatusEx (&statex);
			return statex;
		}

		LongIndex getAvailableMemory()
		{
			return getFreeMemory();
		}

		LongIndex getFreeMemory()
		{
			MEMORYSTATUSEX statex = getMemoryStatus();
			return static_cast<LongIndex>(statex.ullAvailPhys);
		}

		LongIndex getTotalMemory()
		{
			MEMORYSTATUSEX statex = getMemoryStatus();
			return static_cast<LongIndex>(statex.ullTotalPhys);
		}

		LongIndex getBufferedMemory()
		{
			return 0;
		}

		Time getUptime()
		{
			return -1;
		}

		Index getNumberOfProcessors()
		{
			SYSTEM_INFO sysinfo;
			GetSystemInfo(&sysinfo);
			return sysinfo.dwNumberOfProcessors;
		}

		LongIndex getFreeSwapSpace()
		{
			MEMORYSTATUSEX statex = getMemoryStatus();
			return (LongIndex) statex.ullAvailPageFile;
		}

#else
#ifdef BALL_OS_DARWIN

		LongIndex getAvailableMemory()
		{
			return getFreeMemory();
		}
 
		bool getDarwinMemstats(LongSize& free, LongSize& total, LongSize& used)
		{
			static mach_port_t host;
			static mach_msg_type_number_t host_size = sizeof(vm_statistics_data_t) / sizeof(Index);
			static vm_size_t page_size;
			static vm_statistics_data_t vm_stats;

			host = mach_host_self();
			host_page_size(host, &page_size);
			if (host_statistics(host, HOST_VM_INFO, (host_info_t)&vm_stats, &host_size) != KERN_SUCCESS)
			{
				return false;
			}
			used = (vm_stats.active_count + vm_stats.inactive_count + vm_stats.wire_count) * page_size;
			free = vm_stats.free_count * page_size;
			total = free + used;
			
			return true;
		}

		LongIndex getFreeMemory()
		{
			static LongSize free, total, used;
			getDarwinMemstats(free, total, used);
			return free;
		}

		LongIndex getTotalMemory()
		{
    	unsigned int physmem;
    	size_t len = sizeof(physmem);
    	static int mib[2] = { CTL_HW, HW_PHYSMEM };

    	if (sysctl (mib, 2, &physmem, &len, NULL, 0) == 0
					&& len == sizeof(physmem))
			{
    	  return (LongIndex) physmem;
			}
			return -1;
		}

		LongIndex getBufferedMemory()
		{
			return -1;

		}

		Time getUptime()
		{
			return -1;
		}

		Index getNumberOfProcessors()
		{
			int mib[2] = { CTL_HW, HW_NCPU };
			int num_proc = 0;
			size_t len = sizeof(num_proc);
			sysctl(mib, 2, &num_proc, &len, NULL, 0);
			return (Index)num_proc;
		}

		LongIndex getFreeSwapSpace()
		{
			return getFreeMemory(); // It's at least this much. If you better, please tell me! [OK]
		}


#else // We have no idea how to retrieve that information on this
			// platform, so we just return -1 everywhere

		LongIndex getAvailableMemory()
		{
			return -1;
		}

		LongIndex getFreeMemory()
		{
			return -1;
		}

		LongIndex getTotalMemory()
		{
			return -1;
		}

		LongIndex getBufferedMemory()
		{
			return -1;
		}

		Time getUptime()
		{
			return -1;
		}

		Index getNumberOfProcessors()
		{
			return -1;
		}
	
		LongIndex getFreeSwapSpace()
		{
			return -1;
		}

#endif
#endif
#endif
#endif

	} // namespace SysInfo

} // namespace BALL

