//_new_file_header


#ifndef BALL_CORE_MOLMEC_CHARMM_CHARMMSTRETCH_H
#define BALL_CORE_MOLMEC_CHARMM_CHARMMSTRETCH_H

#include <BALL/core/molmec/common/stretchComponent.h>


namespace BALL
{
	/**	Charmm bond stretch component
			
    	\ingroup  CHARMM
	*/
	class BALL_EXPORT CharmmStretch : public StretchComponent
	{
		public:

		/// flag to enable Stretches
		#define CHARMM_STRETCHES_ENABLED "enable Stretches"

		/**	@name	Constructors and Destructors	
		*/
		//@{

		BALL_CREATE(CharmmStretch)

		/**	Default constructor.
		*/
		CharmmStretch();

		/**	Constructor.
		*/
		CharmmStretch(ForceField& force_field);

		/**	Destructor.
		*/
		virtual ~CharmmStretch();

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

#endif // BALL_CORE_MOLMEC_CHARMM_CHARMMSTRETCH_H