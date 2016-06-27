//_new_file_header


#ifndef BALL_CORE_SOLVATION_ELECTROSTATICPOTENTIALCALCULATOR_H
#define BALL_CORE_SOLVATION_ELECTROSTATICPOTENTIALCALCULATOR_H

#include <BALL/core/datatype/options.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/structure/defaultProcessors.h>


namespace BALL
{
	class FragmentDB;

	/** This class is used to compute the electrostatic potential for
	    of a system. It is intended that several different models will
			be implemented. Right now, the only model is the nonlocal electrostatic
			potential of a sum of Born ions.
			Dont forget to set the FragmentDB before using this class.
      \ingroup Solvation
	 */
	class BALL_EXPORT ElectrostaticPotentialCalculator
	{
		BALL_CREATE(ElectrostaticPotentialCalculator)

		public:	

		/** Symbolic names for option keys.
		 		This struct contains a symbolic name for each recognized key
				in ElectrostaticPotentialCalculator::options.
		 */
		struct Option
		{
			/** The method to use for the calculation of the electrostatic potential.
			 */
			static const char* LOCALITY;
		};

		/** Default values for the options in ElectrostaticPotentialCalculator::options
		 */
		struct Default
		{
			/** Default calculation method.
			 		The default is to use a local field.
			 */
			static const bool LOCALITY;
		};
			 		
		/** @name Constructors and Destructors
		 */
		//@{
		
		/** Default constructor
		 */
		ElectrostaticPotentialCalculator()
			;

		/** Copy constructor
		 */
		ElectrostaticPotentialCalculator(const ElectrostaticPotentialCalculator& epc)
			;

		/** Destructor.
		 */
		virtual ~ElectrostaticPotentialCalculator()
			;

		//@}
		/** @name Assignment
		 */
		//@{
		
		/** Apply the current model to the System S and prepare everything for a calculation.
		 		@exception NullPointer if FragmentDB is not set
		 */
		void apply(System &S)
			throw(Exception::NullPointer);

		///
		void setFragmentDB(const FragmentDB* db)
			;

		///
		const FragmentDB* getFragmentDB() const
			;

		//@}
		/** @name Accessors
		 */
		//@{
		
		/** Returns the electrostatic potential at position pos.
		 */
		float operator() (const Vector3& pos)
			;

		//@}
		/** @name Options
		 */
		//@{

		/** Options for the calculation of the electrostatic potential.
		 */
		Options options;

		//@}
		/** @name Protected Attributes.
		 */
		//_@{
		protected:

		System mySys_;

		FragmentDB *frag_db_;

		AssignRadiusProcessor radii_;
		
		AssignChargeProcessor charges_;
		//_@}
	};
}

#endif // BALL_CORE_SOLVATION_ELECTROSTATICPOTENTIALCALCULATOR_H
