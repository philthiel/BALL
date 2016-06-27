//_new_file_header


#ifndef BALL_CORE_MATHS_COMPLEX_H
#define BALL_CORE_MATHS_COMPLEX_H

#include <complex>

#ifdef BALL_HAS_FFTW_H
	#include <fftw3.h>
#endif

namespace BALL 
{
	typedef std::complex<BALL_COMPLEX_PRECISION> Complex;
} // namespace BALL

#endif // BALL_CORE_MATHS_COMPLEX_H
