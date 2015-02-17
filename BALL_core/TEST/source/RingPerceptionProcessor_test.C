// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL_core/CONCEPT/classTest.h>
#include <BALLTestConfig.h>

///////////////////////////

#include <BALL_core/QSAR/ringPerceptionProcessor.h>
#include <BALL_core/FORMAT/SDFile.h>
#include <BALL_core/FORMAT/PDBFile.h>
#include <BALL_core/KERNEL/system.h>
#include <BALL_core/KERNEL/atom.h>
#include <BALL_core/KERNEL/bond.h>
#include <BALL_core/KERNEL/forEach.h>
#include <BALL_core/KERNEL/molecule.h>

///////////////////////////
START_TEST(RingPerceptionProcessor)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

using namespace BALL;

SDFile infile(BALL_TEST_DATA_PATH(descriptors_test.sdf));
System S;
infile >> S;
infile.close();

Molecule * molecule;
Size limit = S.countMolecules();

CHECK(RingPerceptionProcessor)	

	RingPerceptionProcessor rpp;
	S.apply(rpp);

	Size results_atoms[9] = {6, 6, 6, 6, 6, 13, 0, 6, 4};
	Size results_bonds[9] = {6, 6, 6, 6, 6, 14, 0, 6, 6};

	for (Size i = 0; i != limit; ++i)
	{
		molecule = S.getMolecule(i);
		Size num_ringed = 0;

		// atoms
		AtomConstIterator a_it = molecule->beginAtom();
		for (; a_it != molecule->endAtom(); ++a_it)
		{
			if (a_it->getProperty("InRing").getBool())
			{		
				++num_ringed;
			}
		}
		TEST_EQUAL(num_ringed, results_atoms[i])

		// bonds
		num_ringed = 0;
		a_it = molecule->beginAtom();
		Atom::BondConstIterator b_it = a_it->beginBond();
		BALL_FOREACH_BOND(*molecule, a_it, b_it)
		{
			if (b_it->getProperty("InRing").getBool())
			{
				++num_ringed;
			}
		}
		TEST_EQUAL(num_ringed, results_bonds[i])
	}
		
RESULT

CHECK(DNA)
	PDBFile pdb(BALL_TEST_DATA_PATH(1BNA.pdb));
	System s2;
	pdb >> s2;
	RingPerceptionProcessor rpp;
	vector<vector<Atom*> > rings;
	s2.apply(rpp);
	rpp.calculateSSSR(rings, s2);
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
