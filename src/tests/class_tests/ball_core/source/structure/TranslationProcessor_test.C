//_new_file_header


#include <BALL/core/concept/classTest.h>

///////////////////////////

#include <BALL/core/structure/geometricTransformations.h>
#include <BALL/core/kernel/fragment.h>

using namespace BALL;

///////////////////////////

START_TEST(TranslationApplictor)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

TranslationProcessor* app;
CHECK(default constructor)
	app = new TranslationProcessor;
	TEST_NOT_EQUAL(app, 0)
RESULT

Vector3	t(0.0, 0.0, 0.0);
CHECK(getTranslation/setTranslation)
	TEST_EQUAL(app->getTranslation(), t)
	t.set(1,2,3);
	app->setTranslation(t);
	TEST_EQUAL(app->getTranslation(), t)
RESULT

CHECK(destructor/constructor)
	delete app;
	app = new TranslationProcessor(t);
	TEST_NOT_EQUAL(app, 0)
	TEST_EQUAL(app->getTranslation(), t)
RESULT

CHECK(operator ())
	using BALL::Fragment;
	using BALL::Atom;

	Fragment* frag = new Fragment;
	Atom* atom1 = new Atom;
	Atom* atom2 = new Atom;
	atom1->setPosition(t);
	t.set(0,0,0);
	atom2->setPosition(t);
	frag->insert(*atom1);
	frag->insert(*atom2);
	frag->apply(*app);
	t.set(1,2,3);
	TEST_EQUAL(atom2->getPosition(), t)
	t *= 2;
	TEST_EQUAL(atom1->getPosition(), t)
	delete frag;
RESULT
delete app;


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
