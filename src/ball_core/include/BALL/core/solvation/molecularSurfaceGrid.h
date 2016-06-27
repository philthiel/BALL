//_new_file_header


#ifndef BALL_CORE_SOLVATION_MOLECULARSURFACEGRID_H
#define BALL_CORE_SOLVATION_MOLECULARSURFACEGRID_H

#include <BALL/core/datatype/regularData3D.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/maths/vector3.h>


namespace BALL 
{

	// Define the entry values for an SES or SAS grid
	BALL_EXPORT extern const char CCONN__INSIDE;
	BALL_EXPORT extern const char CCONN__OUTSIDE;
	BALL_EXPORT extern const char CCONN__INSIDE_PROBE;

	/** calculateSESGrid
	\ingroup Solvation
	*/
	BALL_EXPORT TRegularData3D<char>* calculateSESGrid
		(const Vector3& lower, const Vector3& upper, 
		 float spacing, const System& system, float probe_radius);

	/** calculateSASGrid
	\ingroup Solvation
	*/
	BALL_EXPORT TRegularData3D<char>* calculateSASGrid
		(const Vector3& lower, const Vector3& upper, 
		 float spacing, const System& system, float probe_radius);

   
} // namespace BALL

#endif // BALL_CORE_SOLVATION_MOLECULARSURFACEGRID_H
