//_new_file_header


#include <BALL/core/concept/classTest.h>

///////////////////////////

#include <BALL/core/kernel/predicate.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/kernel/molecule.h>
#include <BALL/core/kernel/atom.h>
#include <BALL/core/kernel/bond.h>
#include <BALL/core/kernel/atomContainer.h>

using namespace BALL;

///////////////////////////

START_TEST(KernelPredicate<T>)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

CHECK(KernelPredicate::operator () (const Composite&) const)
System S;
Molecule M;
Atom A;
M.insert(A);
S.insert(M);

KernelPredicate<System>				system_predicate;
KernelPredicate<Molecule>			molecule_predicate;
KernelPredicate<Atom>					atom_predicate;
KernelPredicate<Bond>					bond_predicate;
KernelPredicate<AtomContainer>	atom_container_predicate;
TEST_EQUAL(system_predicate(S), true)
TEST_EQUAL(system_predicate(M), false)
TEST_EQUAL(system_predicate(A), false)
TEST_EQUAL(molecule_predicate(S), false)
TEST_EQUAL(molecule_predicate(M), true)
TEST_EQUAL(molecule_predicate(A), false)
TEST_EQUAL(atom_predicate(S), false)
TEST_EQUAL(atom_predicate(M), false)
TEST_EQUAL(atom_predicate(A), true)
TEST_EQUAL(bond_predicate(S), false)
TEST_EQUAL(bond_predicate(M), false)
TEST_EQUAL(bond_predicate(A), false)
TEST_EQUAL(atom_container_predicate(S), true)
TEST_EQUAL(atom_container_predicate(M), true)
TEST_EQUAL(atom_container_predicate(A), false)
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
