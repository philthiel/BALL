//_new_file_header


#include <BALL/core/docking/geneticdock/rotateBonds.h>

#include <BALL/core/common/constants.h>
#include <BALL/core/docking/geneticdock/rotateBond.h>
#include <BALL/core/kernel/atom.h>
#include <BALL/core/kernel/bond.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/maths/matrix44.h>
#include <BALL/core/structure/geometricTransformations.h>

#include <iostream>

using namespace std;


namespace BALL
{
	RotateBonds::RotateBonds(const vector<Bond*>* rotatable_bonds)
	{
		for (Size i = 0; i < rotatable_bonds->size(); i++)
		{
			Bond* bond = (*rotatable_bonds)[i];
			Atom* a1 = const_cast<Atom*>(bond->getFirstAtom());
			Atom* a2 = const_cast<Atom*>(bond->getSecondAtom());
			bonds_.push_back(new RotateBond(a1, a2));
		}
	}


	RotateBonds::RotateBonds(const RotateBonds& rb):bonds_(rb.bonds_)
	{
	}

	RotateBonds& RotateBonds::operator = (const RotateBonds& rb)
	{
		if (this == &rb)
		return *this;

		bonds_ = rb.bonds_;

		return *this;
	}

	RotateBonds::~RotateBonds()
	{
		for (Size x = 0; x < bonds_.size(); x++)
			delete bonds_[x];
	}

	void RotateBonds::rotate(std::vector<double> values)
	{
		for (Size x = 0; x < bonds_.size(); x++)
			bonds_[x]->rotate(BALL::Angle((2*values[x] * 3.141)), false);
	}

	int RotateBonds::numberBonds()
	{
		return bonds_.size();
	}
}
