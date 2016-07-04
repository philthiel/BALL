//_new_file_header

#include <BALL/core/concept/classTest.h>

///////////////////////////

#include <BALL/core/kernel/extractors.h>

using namespace BALL;

///////////////////////////

START_TEST(Extractors)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
											
CHECK(AtomList atoms(const AtomContainer& fragment, const String& expression))
	// ????
RESULT

CHECK(AtomList atoms(const AtomContainer& fragment))
	// ????
RESULT

CHECK(AtomList atoms(const AtomList& atoms, const String& expression))
	// ????
RESULT

CHECK(PDBAtomList PDBAtoms(const AtomContainer& fragment, const String& expression))
	// ????
RESULT

CHECK(PDBAtomList PDBAtoms(const AtomContainer& fragment))
	// ????
RESULT

CHECK(BondList bonds(const AtomContainer& fragment, bool selected_only = false))
	// ????
RESULT

CHECK(BondList bonds(const Atom& atom))
	// ????
RESULT

CHECK(AtomContainerList atomContainers(const AtomContainer& fragment, bool selected_only = false))
	// ????
RESULT

CHECK(ResidueList residues(const AtomContainer& fragment, bool selected_only = false))
	// ????
RESULT

CHECK(FragmentList fragments(const AtomContainer& fragment, bool selected_only = false))
	// ????
RESULT

CHECK(MoleculeList molecules(const AtomContainer& fragment, bool selected_only = false))
	// ????
RESULT

CHECK(ProteinList proteins(const AtomContainer& fragment, bool selected_only = false))
	// ????
RESULT

CHECK(SecondaryStructureList secondaryStructures(const AtomContainer& fragment, bool selected_only = false))
	// ????
RESULT

CHECK(ChainList chains(const AtomContainer& fragment, bool selected_only = false))
	// ????
RESULT

CHECK(NucleicAcidList nucleicAcids(const AtomContainer& fragment, bool selected_only = false))
	// ????
RESULT

CHECK(NucleotideList nucleotides(const AtomContainer& fragment, bool selected_only = false))
	// ????
RESULT


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
