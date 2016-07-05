//_new_file_header


#include <BALL/core/structure/bondorders/bondOrderAssignmentStrategy.h>


namespace BALL
{
	BondOrderAssignmentStrategy::BondOrderAssignmentStrategy(AssignBondOrderProcessor* parent)
		: abop(parent)
	{
	}

	bool BondOrderAssignmentStrategy::readOptions(const Options& /*options*/)
	{
		return true;
	}

	void BondOrderAssignmentStrategy::setDefaultOptions()
	{
	}

	void BondOrderAssignmentStrategy::clear()
	{
	}
}
