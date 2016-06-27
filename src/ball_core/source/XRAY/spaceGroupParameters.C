//_new_file_header


#include <BALL/core/xray/spaceGroupParameters.h>

using namespace std;


namespace BALL 
{
	SpaceGroupParameters::SpaceGroupParameters()
		: ParameterSection()
	{
	}
	
	SpaceGroupParameters::~SpaceGroupParameters()
	{
		clear();
	}
	
	void SpaceGroupParameters::clear()
	{
		symops_.clear();	
		ParameterSection::clear();
	}
	
	bool SpaceGroupParameters::extractSpaceGroup(Parameters& parameters, const String& space_group)
	{
		return true;
	}
	
	bool SpaceGroupParameters::extractSpaceGroup(Parameters& parameters, const Position iucr_no)
	{
		return true;
	}
} // namespace BALL
