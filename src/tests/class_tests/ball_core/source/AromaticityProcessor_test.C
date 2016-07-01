// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
//
#include <BALL/core/concept/classTest.h>
#include <testConfig.h>

///////////////////////////

#include <BALL/core/qsar/aromaticityProcessor.h>
#include <BALL/core/format/SDFile.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/kernel/atom.h>
#include <BALL/core/kernel/bond.h>
#include <BALL/core/kernel/forEach.h>
#include <BALL/core/kernel/molecule.h>
#include <BALL/core/kernel/PTE.h>

///////////////////////////
START_TEST(AromaticityProcessor)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

using namespace BALL;

SDFile infile(TEST_DATA_PATH(ball_core/descriptors_test.sdf));
System S;
infile >> S;
infile.close();

Molecule * molecule;
Size limit = S.countMolecules();

CHECK(AromaticityProcessor)	

	AromaticityProcessor ap;
	S.apply(ap);

	
	Size results[] = {0, 6, 0, 6, 6, 6, 0, 6, 0};
	for (Size i=0;i!=limit;++i)
	{
		molecule = S.getMolecule(i);

		// atoms
		Size num_aro = 0;
		AtomConstIterator a_it = molecule->beginAtom();
		for (;a_it!=molecule->endAtom();++a_it)
		{
			if(a_it->hasProperty("IsAromatic"))
			{
				if (a_it->getProperty("IsAromatic").getBool())
				{
					++num_aro;
				}
			}
		}
		TEST_EQUAL(num_aro, results[i])

		// bonds
		a_it = molecule->beginAtom();
		Atom::BondConstIterator b_it = a_it->beginBond();
		num_aro = 0;
		BALL_FOREACH_BOND(*molecule, a_it, b_it)
		{
			if (b_it->getOrder() == Bond::ORDER__AROMATIC)
			{
				++num_aro;
			}
		}
		TEST_EQUAL(num_aro, results[i])		
	}
		
RESULT


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
