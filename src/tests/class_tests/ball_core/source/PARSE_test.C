// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL/core/concept/classTest.h>
#include <testConfig.h>

///////////////////////////

// insert includes here
#include <BALL/core/system/path.h>
#include <BALL/core/format/PDBFile.h>
#include <BALL/core/format/HINFile.h>
#include <BALL/core/format/INIFile.h>
#include <BALL/core/structure/fragmentDB.h>
#include <BALL/core/molmec/common/radiusRuleProcessor.h>
#include <BALL/core/molmec/common/chargeRuleProcessor.h>
#include <BALL/core/structure/defaultProcessors.h>

///////////////////////////

START_TEST(class_name)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

using namespace BALL;

HINFile hinfile;
PDBFile pdbfile;
System system;
System ref_system;
FragmentDB db("");

Path path;
String tmp = path.find("solvation/PARSE.rul");
INIFile PARSE_rule_file(tmp);
PARSE_rule_file.read();
ChargeRuleProcessor charges(PARSE_rule_file);
RadiusRuleProcessor radii(PARSE_rule_file);
AtomConstIterator atom_it;
AtomConstIterator ref_atom_it;
float total_charge;
ClearChargeProcessor clear_charges;

CHECK("AlaGlySer: -CONH-, -OH, COO(-), NH3(+), aliphatic carbons with hydrogens")
	hinfile.open(TEST_DATA_PATH(ball_core/AlaGlySer.hin));
	hinfile >> system;
	hinfile.close();
	system.apply(db.normalize_names);
	system.apply(clear_charges);
	system.apply(charges);
	system.apply(radii);
	for (atom_it = system.beginAtom(), total_charge = 0.0f; +atom_it; ++atom_it)
	{
		total_charge += atom_it->getCharge();
	}
	TEST_REAL_EQUAL(total_charge, 0.0)
	hinfile.open(TEST_DATA_PATH(ball_core/AlaGlySer_PARSE_charges.hin));
	hinfile >> ref_system;
	hinfile.close();
	for (atom_it = system.beginAtom(), ref_atom_it = ref_system.beginAtom();
			+atom_it; ++atom_it, ++ref_atom_it)
	{
		TEST_REAL_EQUAL(atom_it->getCharge(), ref_atom_it->getCharge())
	}
RESULT

CHECK("AspGluAsnGlnArg: -COOH -CONH2 -CONH- -CNC-(NH2)2")
	system.clear();
	hinfile.open(TEST_DATA_PATH(ball_core/AspGluAsnGlnArg.hin));
	hinfile >> system;
	hinfile.close();
	system.apply(db.normalize_names);
	system.apply(clear_charges);
	system.apply(charges);
	system.apply(radii);

	for (atom_it = system.beginAtom(), total_charge = 0.0f; +atom_it; ++atom_it)
	{
		total_charge += atom_it->getCharge();
	}
	TEST_REAL_EQUAL(total_charge, -0.0)
	ref_system.clear();
	hinfile.open(TEST_DATA_PATH(ball_core/AspGluAsnGlnArg_PARSE_charges.hin));
	hinfile >> ref_system;
	hinfile.close();
	for (atom_it = system.beginAtom(), ref_atom_it = ref_system.beginAtom();
			+atom_it; ++atom_it, ++ref_atom_it)
	{
		TEST_REAL_EQUAL(atom_it->getCharge(), ref_atom_it->getCharge())
	}
RESULT

CHECK("PheTyrTrpHisLys+.hin")
	system.clear();
	hinfile.open(TEST_DATA_PATH(ball_core/PheTyrTrpHisLys+.hin));
	hinfile >> system;
	hinfile.close();
	system.apply(db.normalize_names);
	system.apply(clear_charges);
	system.apply(charges);
	system.apply(radii);

	for (atom_it = system.beginAtom(), total_charge = 0.0f; +atom_it; ++atom_it)
	{
		total_charge += atom_it->getCharge();
	}
	TEST_REAL_EQUAL(total_charge, 1.0)
	ref_system.clear();
	hinfile.open(TEST_DATA_PATH(ball_core/PheTyrTrpHisLys+_PARSE_charges.hin));
	hinfile >> ref_system;
	hinfile.close();
	for (atom_it = system.beginAtom(), ref_atom_it = ref_system.beginAtom();
			+atom_it; ++atom_it, ++ref_atom_it)
	{
		TEST_REAL_EQUAL(atom_it->getCharge(), ref_atom_it->getCharge())
	}
RESULT

CHECK("Cys-Asp-Glu-Tyr-His+Arg+.hin")
	system.clear();
	hinfile.open(TEST_DATA_PATH(ball_core/Cys-Asp-Glu-Tyr-His+Arg+.hin));
	hinfile >> system;
	hinfile.close();
	system.apply(db.normalize_names);
	system.apply(clear_charges);
	system.apply(charges);
	system.apply(radii);

	for (atom_it = system.beginAtom(), total_charge = 0.0f; +atom_it; ++atom_it)
	{
		total_charge += atom_it->getCharge();
	}
	TEST_REAL_EQUAL(total_charge, -2.0)
	ref_system.clear();
	hinfile.open(TEST_DATA_PATH(ball_core/Cys-Asp-Glu-Tyr-His+Arg+_PARSE_charges.hin));
	hinfile >> ref_system;
	hinfile.close();
	for (atom_it = system.beginAtom(), ref_atom_it = ref_system.beginAtom();
			+atom_it; ++atom_it, ++ref_atom_it)
	{
		TEST_REAL_EQUAL(atom_it->getCharge(), ref_atom_it->getCharge())
	}
RESULT


CHECK("SerThrLysCysMet.hin")
	system.clear();
	hinfile.open(TEST_DATA_PATH(ball_core/SerThrLysCysMet.hin));
	hinfile >> system;
	hinfile.close();
	system.apply(db.normalize_names);
	system.apply(clear_charges);
	system.apply(charges);
	system.apply(radii);

	for (atom_it = system.beginAtom(), total_charge = 0.0f; +atom_it; ++atom_it)
	{
		total_charge += atom_it->getCharge();
	}
	TEST_REAL_EQUAL(total_charge, 0.0)
	ref_system.clear();
	hinfile.open(TEST_DATA_PATH(ball_core/SerThrLysCysMet_PARSE_charges.hin));
	hinfile >> ref_system;
	hinfile.close();
	for (atom_it = system.beginAtom(), ref_atom_it = ref_system.beginAtom();
			+atom_it; ++atom_it, ++ref_atom_it)
	{
		TEST_REAL_EQUAL(atom_it->getCharge(), ref_atom_it->getCharge())
	}
RESULT


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
