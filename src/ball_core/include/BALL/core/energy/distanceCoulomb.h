//_new_file_header


#ifndef BALL_CORE_ENERGY_DISTANCE_COULOMB_H
#define BALL_CORE_ENERGY_DISTANCE_COULOMB_H

#include <BALL/core/common/macros.h>


namespace BALL 
{
	class AtomContainer;

	/**	Returns the electrostatic (self) energy of a molecular system.
			Units are kJ/mol. Charges have to be assigned to each atom prior to a call
			to calculateDistanceCoulomb. Dielectric constant is calculated as follows:
			\f[\mathrm
				\varepsilon = 4 r_{ij}\nonumber
			\f]
			@see	Atom::setCharge
			@see	AssignChargeProcessor
    	
			\ingroup  Electrostatic
	*/
	BALL_EXPORT double calculateDistanceCoulomb(const AtomContainer& fragment);
} // namespace BALL

#endif //  BALL_CORE_ENERGY_DISTANCE_COULOMB_H
