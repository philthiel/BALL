//_new_file_header


#include <BALL/core/concept/processor.h>
#include <BALL/core/datatype/hashGrid.h>

namespace BALL
{

	class TestProcessor
		:	public UnaryProcessor<int>
	{
		virtual Processor::Result operator () (int& arg)
			throw()
		{
			arg++;
			return Processor::CONTINUE;
		}
	};

	class TestProcessor2
		:	public UnaryProcessor<HashGridBox3<int> >
	{
		virtual Processor::Result operator () (HashGridBox3<int>& arg)
			throw()
		{
			TestProcessor proc;
			arg.apply(proc);
			return Processor::CONTINUE;
		}
	};
}
