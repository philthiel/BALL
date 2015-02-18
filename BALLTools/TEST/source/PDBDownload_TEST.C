// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

// Mandatory includes
#include <BALLTools/toolTest.h>
#include <BALLToolsTestConfig.h>


using namespace BALL;
using namespace std;


START_TEST(PDBDownloader)
/////////////////////////////////////////////////////////////

String toolname = "PDBDownload";

CHECK(PDBDownload: file download in PDB format)
	String filename;
	NEW_TMP_FILE(filename);

	EXECUTE_TOOL_BEGIN(PDBDownload)
	"-id", "3qp0", "-o", filename.c_str()
	EXECUTE_TOOL_END()

	if (TEST::exit_status == 2)
	{
		// No valid network connection
		STATUS("No network connection - cannot test PDBDownload");
	}
	else
	{
		TEST_EQUAL(TEST::exit_status, 0)
		TEST_FILE_REGEXP(filename.c_str(), TOOLS_TEST_DATA_PATH(PDBFile_01.pdb))
	}
RESULT

CHECK(PDBDownload: file download in XML format)
	String filename;
	NEW_TMP_FILE(filename);

	EXECUTE_TOOL_BEGIN(PDBDownload)
	"-id", "3qp0", "-o", filename.c_str(), "-format", "xml"
	EXECUTE_TOOL_END()

	if (TEST::exit_status == 2)
	{
		// No valid network connection
		STATUS("No network connection - cannot test PDBDownload");
	}
	else
	{
		TEST_EQUAL(TEST::exit_status, 0)
		TEST_FILE_REGEXP(filename.c_str(), TOOLS_TEST_DATA_PATH(PDBFile_01.xml))
	}
RESULT

CHECK(PDBDownload: file download in CIF format)
	String filename;
	NEW_TMP_FILE(filename);

	EXECUTE_TOOL_BEGIN(PDBDownload)
	"-id", "3qp0", "-o", filename.c_str(), "-format", "cif"
	EXECUTE_TOOL_END()

	if (TEST::exit_status == 2)
	{
		// No valid network connection
		STATUS("No network connection - cannot test PDBDownload");
	}
	else
	{
		TEST_EQUAL(TEST::exit_status, 0)
		TEST_FILE_REGEXP(filename.c_str(), TOOLS_TEST_DATA_PATH(PDBFile_01.cif))
	}
RESULT


/////////////////////////////////////////////////////////////
END_TEST
