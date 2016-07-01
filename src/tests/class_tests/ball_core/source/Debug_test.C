//_new_file_header


#include <BALL/config.h>
// Make sure the debug flag is set, independent of what configure says
#define BALL_DEBUG
#include <BALL/core/common/debug.h>

#include <BALL/core/concept/classTest.h>

///////////////////////////

START_TEST(COMMON_debug)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

using namespace BALL;

CHECK(BALL_PRECONDITION_EXCEPTION(condition, message))
	TEST_EXCEPTION(Exception::Precondition, BALL_PRECONDITION_EXCEPTION(1 == 0, "test1"))
	BALL_PRECONDITION_EXCEPTION(1 == 1, "test2")
RESULT

CHECK(BALL_POSTCONDITION_EXCEPTION(condition, message))
	TEST_EXCEPTION(Exception::Postcondition, BALL_POSTCONDITION_EXCEPTION(1 == 0, "test1"))
	BALL_POSTCONDITION_EXCEPTION(1 == 1, "test2")
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
