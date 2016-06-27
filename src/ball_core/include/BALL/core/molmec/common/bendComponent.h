//_new_file_header


#ifndef BALL_CORE_MOLMEC_COMMON_BENDCOMPONENT_H
#define BALL_CORE_MOLMEC_COMMON_BENDCOMPONENT_H

#include <BALL/core/molmec/common/forceFieldComponent.h>
#include <BALL/core/molmec/parameter/quadraticAngleBend.h>

#include <vector>


namespace BALL
{
	class ForceField;
	/**	Amber bond stretch component
			
		\ingroup  COMMON
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
			std::vector<QuadraticAngleBend::Data> bend_;

			QuadraticAngleBend bend_parameters_;

			//_@}
	};
} // namespace BALL

#endif // BALL_MOLMEC_COMMON_BENDCOMPONENT_H
