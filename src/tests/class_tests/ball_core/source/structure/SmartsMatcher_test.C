//_new_file_header


#include <BALL/core/concept/classTest.h>
#include <BALL/test/testConfig.h>

///////////////////////////

#include <BALL/core/structure/smartsMatcher.h>
#include <BALL/core/format/SDFile.h>
#include <BALL/core/kernel/system.h>

using namespace std;
using namespace BALL;

///////////////////////////

START_TEST(SmartsMatcher)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

SmartsMatcher* sm = 0;

CHECK(SmartsMatcher())
	sm = new SmartsMatcher();
RESULT

CHECK(~SmartsMatcher())
	delete sm;
RESULT

CHECK(match(Molecule& mol, const String& smarts))

	SDFile infile(TEST_DATA_PATH(ball_core/SmartsMatcher_test.sdf));
	System s;
	infile >> s;
	infile.close();

	sm = new SmartsMatcher();

	ifstream is(TEST_DATA_PATH(ball_core/SmartsMatcher_test.txt));
	String line;

	while (line.getline(is))
	{
		String tmp(line);
		tmp.trim();
		vector<String> split;
		tmp.split(split, " ");
		
		vector<set<const Atom*> > matchings;
		sm->match(matchings, *s.getMolecule(0), split[2]);
		TEST_EQUAL(matchings.size(), split[0].toUnsignedInt())
	}

	delete sm;	
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

END_TEST
