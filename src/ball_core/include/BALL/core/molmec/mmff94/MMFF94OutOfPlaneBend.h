//_new_file_header


#ifndef BALL_CORE_MOLMEC_MMFF94_MMFF94OUTOFPLANEBEND_H
#define BALL_CORE_MOLMEC_MMFF94_MMFF94OUTOFPLANEBEND_H

#include <BALL/core/molmec/common/forceField.h>
#include <BALL/core/molmec/common/forceFieldComponent.h>
#include <BALL/core/molmec/mmff94/MMFF94Parameters.h>

#include <vector>


namespace BALL 
{
	/**	MMFF94 Out of plane component
    	\ingroup  MMFF94
	*/
	class BALL_EXPORT MMFF94OutOfPlaneBend 
		: public ForceFieldComponent
	{
		public:

		struct BALL_EXPORT OutOfPlaneBend
		{
			Atom *i, *j, *k, *l;
			double k_oop;
			// debug
			double energy;  
		};

		/// flag to enable OutOfPlane
		#define MMFF94_OUTOFPLANE_ENABLED "enable OutOfPlane"

		BALL_CREATE(MMFF94OutOfPlaneBend)

		///	Default constructor.
		MMFF94OutOfPlaneBend();

		///	Constructor.
		MMFF94OutOfPlaneBend(ForceField& force_field);

		///	Copy constructor
		MMFF94OutOfPlaneBend(const MMFF94OutOfPlaneBend& to_copy);

		///	Destructor.
		virtual ~MMFF94OutOfPlaneBend();

		///	Setup method.
		virtual bool setup()
			throw(Exception::TooManyErrors);

		///	Calculates and returns the component's energy.
		virtual double updateEnergy();

		///	Calculates and returns the component's forces.
		virtual void updateForces();

		///
		const std::vector<OutOfPlaneBend>& getOutOfPlaneBends() const { return bends_;}
		
		// Add a double precision TVector3 to a single precision Vector3
		inline void AddDV3_(Vector3& f3, const TVector3<double> d3);

		private:
		std::vector<OutOfPlaneBend> bends_;
		MMFF94PlaneParameters parameters_;
	};

} // namespace BALL

#endif // BALL_CORE_MOLMEC_MMFF94_MMFF94OUTOFPLANEBEND_H
