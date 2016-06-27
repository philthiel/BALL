//_new_file_header


#ifndef BALL_CORE_XRAY_SPACEGROUPPARAMETERS_H
#define BALL_CORE_XRAY_SPACEGROUPPARAMETERS_H

#include <BALL/core/format/parameterSection.h>
#include <BALL/core/maths/matrix44.h>


namespace BALL 
{
	/** SpaceGroupParameters.
			
    	\ingroup  XRay
	*/
	class BALL_EXPORT SpaceGroupParameters 
		:	public ParameterSection
	{
		public:

		/**	Default constructor.
		*/
		SpaceGroupParameters();

		virtual ~SpaceGroupParameters();
		virtual void clear();
		virtual bool extractSpaceGroup(Parameters& parameters, const String& space_group);
		virtual bool extractSpaceGroup(Parameters& parameters, const Position iucr_no);
		//std::vector<Matrix4x4> getSymMatrices();

		protected:
		
		std::vector<Matrix4x4> symops_;
	};
} // namespace BALL

#endif // BALL_CORE_XRAY_SPACEGROUPPARAMETERS_H
