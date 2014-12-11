#include <BALL_core/STRUCTURE/mutator.h>

#include <BALL_core/STRUCTURE/fragmentDB.h>

namespace BALL
{

#ifdef BALL_DEBUG
# include <BALL_core/STRUCTURE/mutator.iC>
#endif

	Mutator::Mutator(FragmentDB* db)
		: db_(db), keep_db_(true)
	{
	}

	Mutator::~Mutator()
	{
		freeDB_();
	}

	void Mutator::setup()
	{
		if(!db_) {
			keep_db_ = false;
			db_ = new FragmentDB("");
		}
	}

	void Mutator::mutate(MutatorOptions opts)
	{
		setup();

		mutate_impl_(opts);

		if(opts & OPTIMIZE) {
			optimize();
		}
	}

	void Mutator::freeDB_()
	{
		if(!keep_db_ && db_) {
			delete db_;
			db_ = 0;
		}
	}

}

