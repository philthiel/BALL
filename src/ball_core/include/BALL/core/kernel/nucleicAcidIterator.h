//_new_file_header


#ifndef BALL_CORE_KERNEL_NUCLEICACIDITERATOR_H
#define BALL_CORE_KERNEL_NUCLEICACIDITERATOR_H

#include <BALL/core/kernel/iterator.h>
#include <BALL/core/kernel/nucleicAcid.h>
#include <BALL/core/kernel/predicate.h>


namespace BALL 
{
	class NucleicAcid;

	/** NucleicAcidIteratorTraits
	
			\ingroup  KernelIterators
	*/
	class BALL_EXPORT NucleicAcidIteratorTraits
		: public CompositeIteratorTraits
	{
		public:

		NucleicAcidIteratorTraits()
			:	CompositeIteratorTraits()
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<NucleicAcid> >();
		}
			
		NucleicAcidIteratorTraits(const Composite& composite)
			:	CompositeIteratorTraits(composite)
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<NucleicAcid> >();
		}
			
		NucleicAcidIteratorTraits(const NucleicAcidIteratorTraits& traits, bool /* deep */ = true)
			:	CompositeIteratorTraits(traits)
		{
		}
			
		NucleicAcidIteratorTraits& operator =(const NucleicAcidIteratorTraits& traits)
		{
			CompositeIteratorTraits::operator=(traits);
			return *this;
		}

		void resetPredicate()
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<NucleicAcid> >();
		}
	};



	typedef BidirectionalIterator
		<Composite, NucleicAcid, Composite::CompositeIterator, NucleicAcidIteratorTraits>
		NucleicAcidIterator;

	typedef ConstBidirectionalIterator
		<Composite, NucleicAcid, Composite::CompositeIterator, NucleicAcidIteratorTraits>
		NucleicAcidConstIterator;

	typedef std::reverse_iterator<NucleicAcidIterator> NucleicAcidReverseIterator;

	typedef std::reverse_iterator<NucleicAcidConstIterator> NucleicAcidConstReverseIterator;

	IteratorWrapper(NucleicAcid)
	ConstIteratorWrapper(NucleicAcid)
} // namespace BALL

#endif // BALL_CORE_KERNEL_NUCLEICACIDITERATOR_H
