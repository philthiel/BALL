//_new_file_header


#ifndef BALL_CORE_MOLMEC_AMBER_AMBERSTRETCH_H
#define BALL_CORE_MOLMEC_AMBER_AMBERSTRETCH_H

#include <BALL/core/molmec/common/stretchComponent.h>


namespace BALL
{
	/**	Amber bond stretch component
			
    	\ingroup  AMBER
	*/
	class BALL_EXPORT AmberStretch : public StretchComponent
	{
		public:

		/// flag to enable Stretches
		#define AMBER_STRETCH_ENABLED "enable Stretches"

		/**	@name	Constructors and Destructors	
		*/
		//@{

		BALL_CREATE(AmberStretch)

		/**	Default constructor.
		*/
		AmberStretch();

		/**	Constructor.
		*/
		AmberStretch(ForceField& force_field);

		/**	Destructor.
		*/
		virtual ~AmberStretch();

		//@}
		/**	@name Setup Methods	
		*/
		//@{

		/**	Setup method.
		*/
		virtual bool setup() throw(Exception::TooManyErrors);

		//@}
	};
} // namespace BALL

#endif // BALL_CORE_MOLMEC_AMBER_AMBERSTRETCH_H
