//_new_file_header


#include <BALL/core/concept/autoDeletable.h>


namespace BALL 
{	
	void* AutoDeletable::last_ptr_ = 0;

#	ifdef BALL_NO_INLINE_FUNCTIONS
#		include <BALL/core/concept/autoDeletable.iC>
#	endif

} // namespace BALL
