//_new_file_header


#include <BALL/core/maths/complex.h>


// AR: obsolete now by using of the C++-datatype complex<.> and new FFTW3
//     Can be removed in future
namespace BALL
{
	#ifdef BALL_HAS_FFTW
	std::istream& operator >> (std::istream& s, fftw_complex& cpx)
	{
		return s >> cpx[0] >> cpx[1];
	}

	std::ostream& operator << (std::ostream& s, const fftw_complex& cpx)
	{	
		return s << cpx[0] << " " << cpx[1];
	}
	#endif

}
