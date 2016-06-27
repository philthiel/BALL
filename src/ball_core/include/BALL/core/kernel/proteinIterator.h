//_new_file_header


#ifndef BALL_CORE_KERNEL_PROTEINITERATOR_H
#define BALL_CORE_KERNEL_PROTEINITERATOR_H

#include <BALL/core/kernel/iterator.h>
#include <BALL/core/kernel/protein.h>
#include <BALL/core/kernel/predicate.h>


namespace BALL 
{
  /** ProteinIteratorTraits 
			
			\ingroup  KernelIterators
	*/
	class BALL_EXPORT ProteinIteratorTraits
		: public CompositeIteratorTraits
	{
		public:

		ProteinIteratorTraits()
			:	CompositeIteratorTraits()
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<Protein> >();
		}
			
		ProteinIteratorTraits(const Composite& composite)
			:	CompositeIteratorTraits(composite)
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<Protein> >();
		}
			
		ProteinIteratorTraits(const ProteinIteratorTraits& traits, bool /* deep */ = true)
			:	CompositeIteratorTraits(traits)
		{
		}
			
		ProteinIteratorTraits& operator = (const ProteinIteratorTraits& traits)
		{
			CompositeIteratorTraits::operator=(traits);
			return *this;
		}

		void resetPredicate()
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<Protein> >();
		}
	};


	///
	typedef BidirectionalIterator
		<Composite, Protein, Composite::CompositeIterator,ProteinIteratorTraits>
		ProteinIterator;

	///
	typedef ConstBidirectionalIterator
		<Composite, Protein, Composite::CompositeIterator, ProteinIteratorTraits>
		ProteinConstIterator;

	///
	typedef std::reverse_iterator<ProteinIterator> ProteinReverseIterator;

	///
	typedef std::reverse_iterator<ProteinConstIterator> ProteinConstReverseIterator;

	IteratorWrapper(Protein)
	ConstIteratorWrapper(Protein)
} // namespace BALL 

#endif // BALL_CORE_KERNEL_PROTEINITERATOR_H
