//_new_file_header

#ifndef BALL_CORE_QSAR_NMRDESCRIPTORS_H
#define BALL_CORE_QSAR_NMRDESCRIPTORS_H

#include <BALL/core/datatype/hashMap.h>
#include <BALL/core/kernel/atomContainer.h>
#include <BALL/core/kernel/protein.h>
#include <BALL/core/kernel/residue.h>


namespace BALL
{

	/**	Calculate the Chi Angles for each residue.
			This method computes the chi angle of each residue and stores it in the given hash map.  
			All angles are in radian. Note, that the hash map is NOT cleaned up, but the results are
			appended to it.
			@param  residue_angles a hash map containing the chi angles of the residues (returned)
			@param	fragment the kernel object containing the residues
	*/
	BALL_EXPORT void calculateResidueChiAngles(const Protein& protein, HashMap<const Residue*, float>& residue_angles);

		/**	Calculate the Chi Angles for each residue.
			This method computes the chi angle of each residue and stores it in the given hash map.  
			All angles are in radian. Note, that the hash map is NOT cleaned up, but the results are
			appended to it.
			@param  residue_angles a hash map containing the chi angles of the residues (returned)
			@param	fragment the kernel object containing the residues
	*/
	BALL_EXPORT void calculateResidueChiAngles(	const Chain& fragment, 
																							HashMap<const Residue*,float>& residue_angles);
	
	/**	Calculate the Chi Angles for a given residue in radian. 
	 * If the given residue has no chi angle, zero is returned.
	*/
	BALL_EXPORT float calculateResidueChiAngles(const Residue& residue);


	/**	Calculate the Chi2 Angles for each residue.
			This method computes the chi2 angle of each residue and stores it in the given hash map.    
			All angles are in radian. Note, that the hash map is NOT cleaned up, but the results are
			appended to it.
			@param  residue_angles a hash map containing the chi2 angles the residues (returned)
			@param	fragment the kernel object containing the residues
	*/
	BALL_EXPORT void calculateResidueChi2Angles(const Protein& protein, HashMap<const Residue*, float>& residue_angles);

	/**	Calculate the Chi2 Angles for each residue.
			This method computes the chi2 angle of each residue and stores it in the given hash map.  
			All angles are in radian.  Note, that the hash map is NOT cleaned up, but the results are
			appended to it.
			@param  residue_angles a hash map containing the chi2 angles of the residues (returned)
			@param	fragment the kernel object containing the residues
	*/
	BALL_EXPORT void calculateResidueChi2Angles(	const Chain& fragment, 
																							HashMap<const Residue*,float>& residue_angles);
	
	
	/**	Calculate the Chi2 Angles for a given residue in radian. 
	 * If the given residue has no chi angle, zero is returned.
	*/
	BALL_EXPORT float calculateResidueChi2Angles(const Residue& residue);

}

#endif // BALL_CORE_QSAR_NMRDESCRIPTORS_H