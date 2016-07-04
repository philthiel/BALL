//_new_file_header


#include <BALL/core/concept/classTest.h>
#include <BALL/test/testConfig.h>

///////////////////////////

#include <BALL/core/structure/surfaceProcessor.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/format/HINFile.h>

#include <list>

using namespace std;
using namespace BALL;

///////////////////////////

START_TEST(SurfaceProcessor)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

SurfaceProcessor* surface_processor_ptr = 0;

CHECK(default constructor)
	surface_processor_ptr = new SurfaceProcessor;
	TEST_NOT_EQUAL(surface_processor_ptr, 0)
RESULT

CHECK(destructor)
	delete surface_processor_ptr;
RESULT

CHECK(getSurface())
	SurfaceProcessor proc;
	Surface empty_surface;
	TEST_EQUAL((proc.getSurface() == empty_surface), true)
RESULT

// ... all obvious test missing

CHECK(SurfaceProcessor / single atom)
	HINFile infile(TEST_DATA_PATH(ball_core/SurfaceProcessor_test_single_atom.hin));
	System system;
	infile >> system;
	infile.close();
	TEST_EQUAL(system.countAtoms(), 1)

	SurfaceProcessor proc;
	system.apply(proc);
	Surface surface = proc.getSurface();
	TEST_EQUAL(surface.getNumberOfTriangles(), 320)
	TEST_EQUAL(surface.getNumberOfVertices(), 162)
RESULT

CHECK(SurfaceProcessor / methane)
	HINFile infile(TEST_DATA_PATH(ball_core/methane.hin));
	System system;
	infile >> system;
	infile.close();
	TEST_EQUAL(system.countAtoms(), 5)

	SurfaceProcessor proc;
	system.apply(proc);
	Surface surface = proc.getSurface();
	TEST_EQUAL(surface.getNumberOfTriangles(), 422)
	TEST_EQUAL(surface.getNumberOfVertices(), 213)
RESULT

/////////////////////////////////////////////////////////////
END_TEST

