//_new_file_header


#include <BALL/core/concept/classTest.h>

///////////////////////////

#include <BALL/core/kernel/atomContainer.h>

#include <algorithm>

using namespace BALL;

///////////////////////////

START_TEST(AtomIterator)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

CHECK(typedefs)
	AtomContainer ac;
	ac.append(*new Atom);
	ac.beginAtom()->setName("A1");
	AtomIterator ai = ac.beginAtom();
	AtomIterator::value_type value = *ai;
	TEST_EQUAL(value.getName(), ai->getName())
	AtomIterator::reference ref = *ai;
	TEST_EQUAL(ref.getName(), ai->getName())
	AtomIterator::pointer ptr = &*ai;
	TEST_EQUAL(ptr, &*ai)
RESULT

CHECK(use in copy algorithm)
	AtomContainer ac;
	Atom a1;
	a1.setName("A1");
	Atom a2;
	a2.setName("A2");
	Atom a3;
	a3.setName("A3");
	
	ac.append(a1);
	ac.append(a2);
	ac.append(a3);
		
	std::vector<Atom> atom_vec(10);
	std::copy(ac.beginAtom(), ac.endAtom(), atom_vec.begin());
	
	TEST_EQUAL(atom_vec[0].getName(), "A1")
	TEST_EQUAL(atom_vec[1].getName(), "A2")
	TEST_EQUAL(atom_vec[2].getName(), "A3")
	TEST_EQUAL(atom_vec[3].getName(), "")
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
