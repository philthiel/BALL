//_new_file_header


#ifndef BALL_CORE_MOLMEC_MMFF94_MMFF94TORSION_H
#define BALL_CORE_MOLMEC_MMFF94_MMFF94TORSION_H

#include <BALL/core/molmec/common/forceField.h>
#include <BALL/core/molmec/common/forceFieldComponent.h>
#include <BALL/core/molmec/mmff94/MMFF94Parameters.h>

#include <vector>


namespace BALL 
{
	/**	MMFF94 bond stretch component
    	\ingroup  MMFF94
	*/
	class BALL_EXPORT MMFF94Torsion 
		: public ForceFieldComponent
	{
		public:

		/// see MMFFTOR.PAR
		struct BALL_EXPORT Torsion
		{
			Torsion();

			Index type;
			Atom* atom1;
			Atom* atom2;
			Atom* atom3;
			Atom* atom4;
			double v1, v2, v3;
			// for debugging:
			double energy; 
			double angle;
			bool heuristic;
		};

		/**	@name	Type Definitions	
		*/
		//@{

		/// flag to enable Torsions
		#define MMFF94_TORSIONS_ENABLED "enable Torsions"
		//@}	

		/**	@name	Constructors and Destructors	
		*/
		//@{

		BALL_CREATE(MMFF94Torsion)

		/**	Default constructor.
		*/
		MMFF94Torsion();

		/**	Constructor.
		*/
		MMFF94Torsion(ForceField& force_field);

		/**	Copy constructor
		*/
		MMFF94Torsion(const MMFF94Torsion& MMFF94_stretch);

		/**	Destructor.
		*/
		virtual ~MMFF94Torsion();

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

		///
		Position getTorsionType(const std::vector<Atom*>& atoms) const;
		
		///
		const std::vector<Torsion>& getTorsions() const { return torsions_;}

		//@}

		protected:

		// Add a double precision TVector3 to a single precision Vector3
		inline void AddDV3_(Vector3& f3, const TVector3<double> d3);

		double getU_(Position e);
		double getV_(Position e);
		bool calculateHeuristic_(const Atom& aj, const Atom& ak, double& v1, double& v2, double& v3);

		std::vector<Torsion> torsions_;
		MMFF94TorsionParameters parameters_;
	};
} // namespace BALL 

#endif // BALL_CORE_MOLMEC_MMFF94_MMFF94TORSION_H