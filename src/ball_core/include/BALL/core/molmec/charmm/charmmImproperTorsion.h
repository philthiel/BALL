//_new_file_header


#ifndef BALL_CORE_MOLMEC_CHARMM_CHARMMIMPROPERTORSION_H
#define BALL_CORE_MOLMEC_CHARMM_CHARMMIMPROPERTORSION_H

#include <BALL/core/molmec/common/forceField.h>
#include <BALL/core/molmec/common/forceFieldComponent.h>
#include <BALL/core/molmec/parameter/quadraticImproperTorsion.h>
#include <BALL/core/molmec/parameter/residueTorsions.h>

#include <vector>


namespace BALL 
{
	/**	Charmm improper torsion component.
			The CHARMM force field employs a harmonic out-of-plane potential for improper
			torsions.	An imporper torsion is defined for four atoms <i>  A </i>, <i>  B </i>, <i>  C </i>,
			and <i>  D </i> where <i>  A </i> is the central atom <i>  B </i>, <i>  C </i>, and <i>  D </i> are bound to. \par
			The out-of-plane-angle <b>  phi </b> is defined as the angle between the planes defined 
			by <i>  ABC </i> and <i>  BCD </i>. 
			The improper torsion energy $E_{imp}$ is then defined as
			$ E_{imp} = k (\theta - \theta_0)^2 $
			where $k$ and $\theta_0$ are constants read from the parameter section and depend on
			the atom types of <i>  A </i>, <i>  B </i>, <i>  C </i>, and <i>  D </i>.	 \par
			
    	\ingroup  CHARMM
	*/
	class BALL_EXPORT CharmmImproperTorsion 
		: public ForceFieldComponent
	{
		public:

		/// flag to enable improper torsions
		#define CHARMM_IMPROPER_TORSIONS_ENABLED "enable IT"

		/**	@name	Constructors and Destructors	
		*/
		//@{

		BALL_CREATE(CharmmImproperTorsion)

		/**	Default constructor.
		*/
		CharmmImproperTorsion();

		/**	Constructor.
		*/
		CharmmImproperTorsion(ForceField& force_field);

		/**	Copy constructor
		*/
		CharmmImproperTorsion(const CharmmImproperTorsion& charmm_stretch);

		/**	Destructor.
		*/
		virtual ~CharmmImproperTorsion();

		//@}
		/**	@name	Setup Methods	
		*/
		//@{

		/**	Setup method.
		*/
		virtual bool setup()
			throw(Exception::TooManyErrors);

		//@}
		/**	@name	Accessors	
		*/
		//@{

		/**	Calculates and returns the component's energy.
		*/
		virtual double updateEnergy();

		/**	Calculates and returns the component's forces.
		*/
		virtual void updateForces();

		//@}

		private:

		/*_	@name	Private Attributes
		*/
		//_@{

		/*_	array with the torsions
		*/
		std::vector<QuadraticImproperTorsion::Data>	impropers_;

		QuadraticImproperTorsion								improper_parameters_;

		ResidueTorsions													improper_atoms_;

		//_@}
	 
	};
} // namespace BALL 

#endif // BALL_CORE_MOLMEC_CHARMM_CHARMMIMPROPERTORSION_H
