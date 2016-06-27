//_new_file_header


#ifndef BALL_CORE_KERNEL_PDBATOMITERATOR_H
#define BALL_CORE_KERNEL_PDBATOMITERATOR_H

#include <BALL/core/concept/stdIteratorWrapper.h>
#include <BALL/core/kernel/iterator.h>
#include <BALL/core/kernel/PDBAtom.h>
#include <BALL/core/kernel/predicate.h>


namespace BALL 
{
	/** Traits class for the PDBAtomIterator.
			
    	\ingroup  KernelIterators
	*/
	class BALL_EXPORT PDBAtomIteratorTraits
		:	public CompositeIteratorTraits
	{
		public:

		inline PDBAtomIteratorTraits();
			
		PDBAtomIteratorTraits(const Composite& composite);
			
		inline PDBAtomIteratorTraits(const PDBAtomIteratorTraits& traits);
			
		PDBAtomIteratorTraits& operator = (const PDBAtomIteratorTraits& traits);

		void resetPredicate();
	};

	inline PDBAtomIteratorTraits::PDBAtomIteratorTraits()
		:	CompositeIteratorTraits()
	{
		predicate_ = &RTTI::getDefault<KernelPredicate<PDBAtom> >();
	}

	inline PDBAtomIteratorTraits::PDBAtomIteratorTraits(const PDBAtomIteratorTraits& traits)
		:	CompositeIteratorTraits(traits)
	{
	}

	inline PDBAtomIteratorTraits::PDBAtomIteratorTraits(const Composite& composite)
		:	CompositeIteratorTraits(composite)
	{
		predicate_ = &RTTI::getDefault<KernelPredicate<PDBAtom> >();
	}

	inline PDBAtomIteratorTraits& PDBAtomIteratorTraits::operator = (const PDBAtomIteratorTraits& traits)
	{
		CompositeIteratorTraits::operator=(traits);
		return *this;
	}

	inline void PDBAtomIteratorTraits::resetPredicate()
	{
		predicate_ = &RTTI::getDefault<KernelPredicate<PDBAtom> >();
	}


	/** @name Iterator type definitions for the various PDBAtomIterators
    	\ingroup  KernelIterators
	*/
	//@{

	/// A mutable bidirectional iterator for the PDBAtom class.
	typedef BidirectionalIterator<Composite, PDBAtom, Composite::CompositeIterator, PDBAtomIteratorTraits>
		PDBAtomIterator;

	/// A constant bidirectional iterator for the PDBAtom class.
	typedef ConstBidirectionalIterator<Composite, PDBAtom, Composite::CompositeIterator, PDBAtomIteratorTraits>
		PDBAtomConstIterator;

	/// A mutable reverse bidirectional iterator for the PDBAtom class.
	typedef std::reverse_iterator<PDBAtomIterator> PDBAtomReverseIterator;

	/// A constant reverse bidirectional iterator for the PDBAtom class.
	typedef std::reverse_iterator<PDBAtomConstIterator> PDBAtomConstReverseIterator;
	//@}

	IteratorWrapper(PDBAtom)
	ConstIteratorWrapper(PDBAtom)
} // namespace BALL

#endif // BALL_CORE_KERNEL_PDBATOMITERATOR_H
