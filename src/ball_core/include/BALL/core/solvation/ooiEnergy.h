//_new_file_header


#ifndef BALL_CORE_SOLVATION_OOIENERGY_H
#define BALL_CORE_SOLVATION_OOIENERGY_H

#include <BALL/core/molmec/common/typeRuleProcessor.h>


namespace BALL 
{
	class AtomContainer;

	/** Calculate the solvation energy after Ooi et al. 
			This function computes the solvation energy using the empirical surface model 
			proposed by Ooi et al.(T. Ooi, M. Oobatake, G. Nemethy, H. A. Scheraga:
			Accessible surface areas as a measure off the thermodynamic parameters
			of hydration of peptides, Proc. Natl. Acad. Sci. USA, Vol. 84 (1987), pp. 3086-3090).
			\par

			The method is parameterized for proteins only. Calling the function with different
			structures probably yields results of arbitrary meaninglessness.
			\par

			The energy is returned in units of kJ/mol.
			Unparametrized atoms are simply ignored, which might lead to unreasonable values.  
			\par
			<b>Files:</b> \par types and parameters are taken from <tt>data/solvation/Ooi.ini</tt> 
			\par
	\ingroup Solvation	
	*/ 
	BALL_EXPORT double calculateOoiEnergy(AtomContainer& atoms);
   	
} // namespace BALL

#endif // BALL_CORE_SOLVATION_OOIENERGY_H
