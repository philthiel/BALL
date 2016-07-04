//_new_file_header


#include <BALL/core/concept/classTest.h>

///////////////////////////

#include <BALL/core/concept/persistentObject.h>
#include <BALL/core/concept/persistenceManager.h>

///////////////////////////

START_TEST(PersistentObject)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

using namespace BALL;

PersistentObject* ptr;

CHECK(PersistentObject::PersistentObject() throw())
	ptr = new PersistentObject;
	TEST_NOT_EQUAL(ptr, 0)
RESULT

CHECK(PersistentObject::~PersistentObject() throw())
	delete ptr;
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
