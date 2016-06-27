//_new_file_header


#ifndef BALL_CORE_ENERGY_COULOMB_H
#define BALL_CORE_ENERGY_COULOMB_H

#include <BALL/core/common/macros.h>


namespace BALL 
{
	class AtomContainer;

	/**	Returns the electrostatic (self) energy of a molecular system.
			Units are kJ/mol. Charges have to be assigned to each atom prior to a call
			to calculateCoulomb()
			@see	Atom::setCharge
			@see	AssignChargeProcessor
			
    	\ingroup  Electrostatic
	*/
	BALL_EXPORT double calculateCoulomb(const AtomContainer& atoms);
} // namespace BALL

#endif // BALL_CORE_ENERGY_COULOMB_H
