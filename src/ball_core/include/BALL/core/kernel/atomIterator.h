//_new_file_header


#ifndef BALL_CORE_KERNEL_ATOMITERATOR_H
#define BALL_CORE_KERNEL_ATOMITERATOR_H

#include <BALL/core/concept/stdIteratorWrapper.h>
#include <BALL/core/kernel/atom.h>
#include <BALL/core/kernel/iterator.h>
#include <BALL/core/kernel/predicate.h>


namespace BALL
{
	/** Traits class for the AtomIterators
			
    	\ingroup  KernelIterators
	*/
	class BALL_EXPORT AtomIteratorTraits
		: public CompositeIteratorTraits
	{
		public:

		inline AtomIteratorTraits()
			:	CompositeIteratorTraits()
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<Atom> >();
		}

		inline AtomIteratorTraits(const AtomIteratorTraits& traits)

			:	CompositeIteratorTraits(traits)
		{
		}

		AtomIteratorTraits(const Composite& composite);

		AtomIteratorTraits& operator = (const AtomIteratorTraits& traits);

		void resetPredicate();
	};


	inline AtomIteratorTraits::AtomIteratorTraits(const Composite& composite)
		:	CompositeIteratorTraits(composite)
	{
		predicate_ = &RTTI::getDefault<KernelPredicate<Atom> >();
	}

	inline AtomIteratorTraits& AtomIteratorTraits::operator = (const AtomIteratorTraits& traits)
	{
		CompositeIteratorTraits::operator = (traits);
		return *this;
	}

	inline void AtomIteratorTraits::resetPredicate()
	{
		predicate_ = &RTTI::getDefault<KernelPredicate<Atom> >();
	}


	/** @name Iterator type definitions for the various AtomIterators
    	\ingroup  KernelIterators
	*/
	//@{

	/** A mutable bidirectional iterator for the Atom class.
	*/
	typedef BidirectionalIterator
		<Composite, Atom, Composite::CompositeIterator, AtomIteratorTraits>
		AtomIterator;

	/** A constant bidirectional iterator for the Atom class.
	*/
	typedef ConstBidirectionalIterator
		<Composite, Atom, Composite::CompositeIterator, AtomIteratorTraits>
		AtomConstIterator;

	/// A mutable reverse bidirectional iterator for the Atom class.
	typedef std::reverse_iterator<AtomIterator> AtomReverseIterator;

	/// A constant reverse bidirectional iterator for the Atom class.
	typedef std::reverse_iterator<AtomConstIterator> AtomConstReverseIterator;

	//@}

	IteratorWrapper(Atom)
	ConstIteratorWrapper(Atom)
} // namespace BALL

#endif // BALL_CORE_KERNEL_ATOMITERATOR_H

