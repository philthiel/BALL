//_new_file_header


#ifndef BALL_CORE_MATHS_FFTWCOMMON_H
#define BALL_CORE_MATHS_FFTWCOMMON_H

#include <fftw3.h>


namespace BALL
{
	struct BALL_EXPORT DoubleTraits
	{
		typedef double ComplexPrecision;
		typedef fftw_plan FftwPlan;
	};
	
	struct BALL_EXPORT FloatTraits
	{
		typedef float ComplexPrecision;
		typedef fftwf_plan FftwPlan;
	};
	
	struct BALL_EXPORT LongDoubleTraits
	{
		typedef long double ComplexPrecision;
		typedef fftwl_plan FftwPlan;
	};
}

#endif // BALL_CORE_MATHS_FFTWCOMMON_H
