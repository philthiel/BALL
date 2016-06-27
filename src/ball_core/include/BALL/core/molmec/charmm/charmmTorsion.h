//_new_file_header


#ifndef BALL_CORE_MOLMEC_CHARMM_CHARMMTORSION_H
#define BALL_CORE_MOLMEC_CHARMM_CHARMMTORSION_H

#include <BALL/core/molmec/common/forceField.h>
#include <BALL/core/molmec/common/forceFieldComponent.h>
#include <BALL/core/molmec/parameter/cosineTorsion.h>
#include <BALL/core/molmec/parameter/residueTorsions.h>

#include <vector>


namespace BALL 
{
	/**	CHARMM torsion component
			
      \ingroup  CHARMM
	*/
	class BALL_EXPORT CharmmTorsion 
		: public ForceFieldComponent
	{
		public:

		/// flag to enable Torsions
		#define CHARMM_TORSIONS_ENABLED "enable Torsions"

		/**	@name	Type Definitions	
		*/
		//@{

		struct SingleCharmmTorsion 
		{
			Atom*	atom1;
			Atom*	atom2;
			Atom*	atom3;
			Atom*	atom4;

			float		V;
			unsigned char	f;
			float		phase;

			SingleCharmmTorsion()
				:	atom1(0),
					atom2(0),
					atom3(0),
					atom4(0),
					V(0),
					f(0),
					phase(0)
			{
			}

			SingleCharmmTorsion(CosineTorsion::SingleData& t)
			{
				atom1 = t.atom1;
				atom2 = t.atom2;
				atom3 = t.atom3;
				atom4 = t.atom4;

				V = t.values.V / t.values.n;
				f = (unsigned char)t.values.f;

				// convert phase from degrees to radiant
				phase = (float)(BALL::Constants::PI / 180.0) * t.values.phase;
			}
		};

		//@}	
		/**	@name	Constructors and Destructors	
		*/
		//@{

		BALL_CREATE(CharmmTorsion)

		/**	Default constructor.
		*/
		CharmmTorsion();

		/**	Constructor.
		*/
		CharmmTorsion(ForceField& force_field);

		/**	Copy constructor
		*/
		CharmmTorsion(const CharmmTorsion& charmm_stretch);

		/**	Destructor.
		*/
		virtual ~CharmmTorsion();

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

		/*_	Vector containing the parameters for each torsion.
		*/
		std::vector<SingleCharmmTorsion> 	torsion_;

		/*_ Contents of the [Torsions] section of the parameter file.
		*/
		CosineTorsion									torsion_parameters_;		

		/*_ Contents of the [ResidueTorsions] section of the parameter file.
		*/
		ResidueTorsions								residue_torsions_;

		/*_	true, if the torsions are read from the ResidueTorsions section.
		*/
		bool use_residue_torsion_list_;

		//_@}
	 
	};
} // namespace BALL 

#endif // BALL_CORE_MOLMEC_CHARMM_CHARMMTORSION_H
