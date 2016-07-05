//_new_file_header


#include <BALL/core/maths/vector3.h>


namespace BALL
{
#ifdef BALL_HAS_EXTERN_TEMPLATES
	template class TVector3<float>;

#ifdef BALL_COMPILER_MSVC
	template class std::vector<Vector3>;
#endif

#endif
}
