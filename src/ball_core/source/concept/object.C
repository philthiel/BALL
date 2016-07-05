//_new_file_header


#include <BALL/core/concept/object.h>

#include <BALL/core/common/macros.h>

using namespace std;


namespace BALL 
{

	Handle Object::global_handle_ = (Handle)0;

	Object::Object()
		
		:	AutoDeletable(),
			handle_(Object::global_handle_++)
	{
	}

	Object::Object(const Object& /* object */)
		
		:	AutoDeletable(),
			handle_(Object::global_handle_++)
	{
	}

	Object::~Object()
		
	{
	}

	void Object::dump(ostream& s, Size depth) const
		
	{
		BALL_DUMP_STREAM_PREFIX(s);

		BALL_DUMP_DEPTH(s, depth);
		BALL_DUMP_HEADER(s, this, this)

		BALL_DUMP_DEPTH(s, depth);
		s << "  handle: " << handle_ << endl;

		BALL_DUMP_DEPTH(s, depth);
		s << "  auto-deletable: " << AutoDeletable::isAutoDeletable() << endl;

		BALL_DUMP_STREAM_SUFFIX(s);
	}

	int Object::compare(const Object & object) const
		
	{
		if (*this == object)
		{
			return 0;
		} 
		if (*this < object)
		{
			return -1;
		} 
		else 
		{
			return 1;
		}
	}


#	ifdef BALL_NO_INLINE_FUNCTIONS
#		include <BALL/core/concept/object.iC>
#	endif

} // namespace BALL


