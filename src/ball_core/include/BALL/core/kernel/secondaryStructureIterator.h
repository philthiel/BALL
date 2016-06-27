//_new_file_header


#ifndef BALL_CORE_KERNEL_SECONDARYSTRUCTUREITERATOR_H
#define BALL_CORE_KERNEL_SECONDARYSTRUCTUREITERATOR_H

#include <BALL/core/kernel/iterator.h>
#include <BALL/core/kernel/predicate.h>
#include <BALL/core/kernel/secondaryStructure.h>


namespace BALL 
{
	/** SecondaryStructureIteratorTraits
	 		
			\ingroup KernelIterators
	*/
	class BALL_EXPORT SecondaryStructureIteratorTraits
		: public CompositeIteratorTraits
	{
		public:
		
		SecondaryStructureIteratorTraits()
			:	CompositeIteratorTraits()
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<SecondaryStructure> >();
		}
			
		SecondaryStructureIteratorTraits(const Composite& composite)
			:	CompositeIteratorTraits(composite)
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<SecondaryStructure> >();
		}
			
		SecondaryStructureIteratorTraits(const SecondaryStructureIteratorTraits& traits, bool /* deep */ = true)
			:	CompositeIteratorTraits(traits)
		{
		}
			
		SecondaryStructureIteratorTraits &operator = (const SecondaryStructureIteratorTraits& traits)
		{
			CompositeIteratorTraits::operator = (traits);
			return *this;
		}

		void resetPredicate()
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<SecondaryStructure> >();
		}
	};


	///
	typedef BidirectionalIterator
		<Composite, SecondaryStructure, Composite::CompositeIterator, SecondaryStructureIteratorTraits>
		SecondaryStructureIterator;

	///
	typedef ConstBidirectionalIterator
		<Composite, SecondaryStructure, Composite::CompositeIterator, SecondaryStructureIteratorTraits>
		SecondaryStructureConstIterator;

	///
	typedef std::reverse_iterator<SecondaryStructureIterator> SecondaryStructureReverseIterator;

	///
	typedef std::reverse_iterator<SecondaryStructureConstIterator> SecondaryStructureConstReverseIterator;

	IteratorWrapper(SecondaryStructure)
	ConstIteratorWrapper(SecondaryStructure)

} // namespace BALL 

#endif // BALL_CORE_KERNEL_SECONDARYSTRUCTUREITERATOR_H
