//_new_file_header


#include <BALL/core/kernel/global.h>
#include <BALL/core/maths/vector3.h>


namespace BALL 
{

	bool clone_bonds = true;
	
	// this is a workaround for the SUNPro CC 6.0ea compiler
	Vector3 BALL_vtable_constructing_vector;

} // namespace BALL
