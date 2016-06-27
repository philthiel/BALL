//_new_file_header


#ifndef BALL_CORE_KERNEL_FRAGMENTITERATOR_H
#define BALL_CORE_KERNEL_FRAGMENTITERATOR_H

#include <BALL/core/concept/stdIteratorWrapper.h>
#include <BALL/core/kernel/iterator.h>
#include <BALL/core/kernel/predicate.h>


namespace BALL 
{
	/** Traits class for the FragmentIterator.
			Intended for internal use only!
			 \par
    	\ingroup  KernelIterators
	*/
	class BALL_EXPORT FragmentIteratorTraits
		: public CompositeIteratorTraits
	{
		public:

		inline FragmentIteratorTraits();

		FragmentIteratorTraits(const Composite& composite);

		inline FragmentIteratorTraits(const FragmentIteratorTraits& traits);

		FragmentIteratorTraits& operator = (const FragmentIteratorTraits& traits);

		void resetPredicate();
	};

	inline FragmentIteratorTraits::FragmentIteratorTraits()
		:	CompositeIteratorTraits()
	{
		predicate_ = &RTTI::getDefault<KernelPredicate<Fragment> >();
	}

	inline FragmentIteratorTraits::FragmentIteratorTraits(const Composite& composite)
		:	CompositeIteratorTraits(composite)
	{
		predicate_ = &RTTI::getDefault<KernelPredicate<Fragment> >();
	}

	inline FragmentIteratorTraits::FragmentIteratorTraits(const FragmentIteratorTraits& traits)
		:	CompositeIteratorTraits(traits)
	{
	}

	inline FragmentIteratorTraits& FragmentIteratorTraits::operator = (const FragmentIteratorTraits& traits)
	{
		CompositeIteratorTraits::operator=(traits);
		return *this;
	}

	inline void FragmentIteratorTraits::resetPredicate()
	{
		predicate_ = &RTTI::getDefault<KernelPredicate<Fragment> >();
	}

	///
	typedef BidirectionalIterator
		<Composite, Fragment, Composite::CompositeIterator, FragmentIteratorTraits>
		FragmentIterator;

	///
	typedef ConstBidirectionalIterator
		<Composite, Fragment, Composite::CompositeIterator, FragmentIteratorTraits>
		FragmentConstIterator;

	///
	typedef std::reverse_iterator<FragmentIterator> FragmentReverseIterator;

	///
	typedef std::reverse_iterator<FragmentConstIterator> FragmentConstReverseIterator;

	IteratorWrapper(Fragment)
	ConstIteratorWrapper(Fragment)

} // namespace BALL 

#endif // BALL_CORE_KERNEL_FRAGMENTITERATOR_H
