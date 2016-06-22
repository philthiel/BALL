// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// Molecular Mechanics: Amber force field, bond stretch component

#ifndef BALL_MOLMEC_COMMON_BENDCOMPONENT_H
#define BALL_MOLMEC_COMMON_BENDCOMPONENT_H

#ifndef BALL_COMMON_H
# include <BALL/core/common.h>
#endif

#ifndef BALL_MOLMEC_COMMON_FORCEFIELDCOMPONENT_H
# include <BALL/core/molmec/common/forceFieldComponent.h>
#endif

#ifndef BALL_MOLMEC_PARAMETER_QUADRATICANGLEBEND_H
# include <BALL/core/molmec/parameter/quadraticAngleBend.h>
#endif

namespace BALL
{
	class ForceField;
	/**	Amber bond stretch component
			
    	\ingroup  AMBER
	*/
	class BALL_EXPORT BendComponent : public ForceFieldComponent
	{
		public:
			BALL_CREATE(BendComponent)

			/** @name	Constructors and Destructors
			*/
			//@{ 

			/**
			 * Default constructor.
			 */
			BendComponent();

			/**
			 * Detailed Constructor.
			 */
			BendComponent(ForceField& force_field);

			/**
			 *Destructor.
			 */
			virtual ~BendComponent();

			//@}

			/**	@name	Accessors	
			*/
			//@{

			/**
			 * \copydoc ForceFieldComponent::updateEnergy()
			 */
			virtual double updateEnergy();

			/**
			 * \copydoc ForceFieldComponent::updateForces()
			 */
			virtual void updateForces();

			//@}

		protected:

			/*_	@name	Private Attributes	
			*/
			//_@{

			/*_	pointer to the array of bends
			*/
			vector<QuadraticAngleBend::Data> bend_;

			QuadraticAngleBend bend_parameters_;

			//_@}
	};
} // namespace BALL

#endif //BALL_MOLMEC_COMMON_BENDCOMPONENT_H
