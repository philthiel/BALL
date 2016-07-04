//_new_file_header


#include <BALL/core/concept/classTest.h>
#include <BALL/test/testConfig.h>

///////////////////////////

#include <BALL/core/format/SDFile.h>
#include <BALL/core/format/PDBFile.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/kernel/atom.h>
#include <BALL/core/kernel/bond.h>
#include <BALL/core/kernel/forEach.h>
#include <BALL/core/kernel/molecule.h>
#include <BALL/core/qsar/ringPerceptionProcessor.h>

using namespace std;
using namespace BALL;

///////////////////////////

START_TEST(RingPerceptionProcessor)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

SDFile infile(TEST_DATA_PATH(ball_core/descriptors_test.sdf));
System S;
infile >> S;
infile.close();

Molecule * molecule;
Size limit = S.countMolecules();

CHECK(RingPerceptionProcessor)	

	RingPerceptionProcessor rpp;

	Size results_atoms[9] = {6, 6, 6, 6, 6, 13, 0, 6, 4};
	Size results_bonds[9] = {6, 6, 6, 6, 6, 14, 0, 6, 6};

	for (Size i = 0; i != limit; ++i)
	{
		molecule = S.getMolecule(i);
		molecule->apply(rpp);
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
	// For some reason this does currently not work!
	// We found that the number of bonds was always lower than the number of
	// atoms in each AtomContainer: thus there could not be any rings.
	// HOWEVER: loading the file in BALLView and using "Count items"
	// always gave the correct result.
	PDBFile pdb(TEST_DATA_PATH(ball_core/1BNA.pdb));
	System s2;
	pdb >> s2;

	RingPerceptionProcessor rpp;
	vector<vector<Atom*> > rings;
	for(AtomContainerIterator mit = s2.beginAtomContainer(); +mit; ++mit)
	{
		rings.clear();
		mit->apply(rpp);
		rpp.calculateSSSR(rings, *mit);
	}

RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
