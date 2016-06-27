//_new_file_header


#ifndef BALL_CORE_KERNEL_RESIDUEITERATOR_H
#define BALL_CORE_KERNEL_RESIDUEITERATOR_H

#include <BALL/core/kernel/iterator.h>
#include <BALL/core/kernel/predicate.h>


namespace BALL 
{
	/** ResidueIteratorTraits
    
			\ingroup  KernelIterators
	*/
	class BALL_EXPORT ResidueIteratorTraits
		: public CompositeIteratorTraits
	{
		public:

		ResidueIteratorTraits()
			:	CompositeIteratorTraits()
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<Residue> >();
		}
			
		ResidueIteratorTraits(const Composite& composite)
			:	CompositeIteratorTraits(composite)
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<Residue> >();
		}
			
		ResidueIteratorTraits(const ResidueIteratorTraits& traits, bool /* deep */ = true)
			:	CompositeIteratorTraits(traits)
		{
		}
			
		ResidueIteratorTraits& operator =(const ResidueIteratorTraits& traits)
		{
			CompositeIteratorTraits::operator=(traits);
			return *this;
		}

		void resetPredicate()
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<Residue> >();
		}
	};


	///
	typedef BidirectionalIterator
		<Composite, Residue, Composite::CompositeIterator, ResidueIteratorTraits>
		ResidueIterator;

	///
	typedef ConstBidirectionalIterator
		<Composite, Residue, Composite::CompositeIterator, ResidueIteratorTraits>
		ResidueConstIterator;

	///
	typedef std::reverse_iterator<ResidueIterator> ResidueReverseIterator;

	///
	typedef std::reverse_iterator<ResidueConstIterator> ResidueConstReverseIterator;

	IteratorWrapper(Residue)
	ConstIteratorWrapper(Residue)
} // namespace BALL

#endif // BALL_CORE_KERNEL_RESIDUEITERATOR_H
