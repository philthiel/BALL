//_new_file_header


#ifndef BALL_CORE_MOLMEC_COMMON_STRETCHCOMPONENT_H
#define BALL_CORE_MOLMEC_COMMON_STRETCHCOMPONENT_H

#include <BALL/core/molmec/common/forceFieldComponent.h>
#include <BALL/core/molmec/parameter/quadraticBondStretch.h>


namespace BALL
{
	class ForceField;

	/**
	 * A ForceField component implementing the harmonic potential used
	 * by Amber and CHARMM
	 * \ingroup MOLMEC
	 */
	class BALL_EXPORT StretchComponent : public ForceFieldComponent
	{
		public:
			BALL_CREATE(StretchComponent)

			/**
			 * Default Constructor
			 */
			StretchComponent();

			/**
			 * Detailed Constructor
			 */
			StretchComponent(ForceField& force_field);

			/**	Destructor.
			*/
			virtual ~StretchComponent();

			//@}

			//@}
			/**	@name Accessors		
			*/
			//@{

			/**
			 * @copydoc ForceFieldComponent::updateEnergy()
			 */
			virtual double updateEnergy();

			/**
			 * @copydoc ForceFieldComponent::updateForces()
			 */
			virtual void updateForces();

			//@} 

		protected:
			/*_	@name	Private Attributes	
			*/
			//_@{

			/*_
			*/
			std::vector<QuadraticBondStretch::Data> stretch_;

			/*_	The stretch parameters section
			*/
			QuadraticBondStretch  stretch_parameters_;

			//_@}
	};
} // namespace BALL

#endif // BALL_CORE_MOLMEC_COMMON_STRETCHCOMPONENT_H
