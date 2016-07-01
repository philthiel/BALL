// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL/core/concept/classTest.h>
#include <testConfig.h>

///////////////////////////

#include <BALL/core/format/SCWRLRotamerFile.h>
#include <BALL/core/structure/rotamerLibrary.h>

///////////////////////////

START_TEST(SCWRLRotamerFile)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

using namespace BALL;
using namespace std;

SCWRLRotamerFile* file_ptr = 0;
CHECK(SCWRLRotamerFile::SCWRLRotamerFile())
	file_ptr = new SCWRLRotamerFile;
	TEST_NOT_EQUAL(file_ptr, 0)
RESULT


CHECK(SCWRLRotamerFile::~SCWRLRotamerFile())
	delete file_ptr;
RESULT


CHECK(SCWRLRotamerFile::SCWRLRotamerFile(const String& filename, File::OpenMode open_mode))
	SCWRLRotamerFile* f = new SCWRLRotamerFile(TEST_DATA_PATH(ball_core/SCWRLRotamerFile_test1.lib)); // bb dep file
	TEST_NOT_EQUAL(f, 0)
	delete f;
RESULT

CHECK(void SCWRLRotamerFile::read >> (RotamerLibrary& library) throw() -- bbdep file)
	SCWRLRotamerFile f(TEST_DATA_PATH(ball_core/SCWRLRotamerFile_test1.lib));// bb depep file
	RotamerLibrary lib;
	lib.clear();
	f >> lib;
	TEST_EQUAL(lib.getNumberOfRotamers(), 4107);
RESULT


CHECK(void readSCWRLBackboneIndependentLibraryFile(RotamerLibrary& library))
	SCWRLRotamerFile f(TEST_DATA_PATH(ball_core/SCWRLRotamerFile_test2.lib)); //bb indndep file
	RotamerLibrary lib;
	f.readSCWRLBackboneIndependentLibraryFile(lib);
	TEST_EQUAL(lib.getNumberOfRotamers(), 110);
RESULT

CHECK(void readSCWRLBackboneDependentLibraryFile(RotamerLibrary& library))
	SCWRLRotamerFile f(TEST_DATA_PATH(ball_core/SCWRLRotamerFile_test1.lib)); // bb depep file
	RotamerLibrary lib;
	lib.clear();
	f.readSCWRLBackboneDependentLibraryFile(lib);
	TEST_EQUAL(lib.getNumberOfRotamers(), 4107);
RESULT

CHECK(void SCWRLRotamerFile::operator >> (RotamerLibrary& library) throw() -- bbdep file)
  SCWRLRotamerFile f(TEST_DATA_PATH(ball_core/SCWRLRotamerFile_test2.lib)); // bb indep file
  RotamerLibrary lib;
  f >> lib;
  TEST_EQUAL(lib.getNumberOfRotamers(), 110);
RESULT

CHECK(const SCWRLRotamerFile& SCWRLRotamerFile::operator = (const SCWRLRotamerFile& file))
  SCWRLRotamerFile f(TEST_DATA_PATH(ball_core/SCWRLRotamerFile_test2.lib)); // bb indep file
  SCWRLRotamerFile copy_of_f;
  copy_of_f = f;
  RotamerLibrary lib;
  copy_of_f >> lib;
  TEST_EQUAL(lib.getNumberOfRotamers(), 110);
RESULT
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
