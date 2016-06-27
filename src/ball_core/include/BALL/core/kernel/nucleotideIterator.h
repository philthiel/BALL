//_new_file_header


#ifndef BALL_CORE_KERNEL_NUCLEOTIDEITERATOR_H
#define BALL_CORE_KERNEL_NUCLEOTIDEITERATOR_H

#include <BALL/core/concept/stdIteratorWrapper.h>
#include <BALL/core/kernel/iterator.h>
#include <BALL/core/kernel/predicate.h>


namespace BALL 
{
	class Nucleotide;

	/** NucleotideIteratorTraits
	 	  \ingroup  KernelIterators
	*/
	class BALL_EXPORT NucleotideIteratorTraits
		: public CompositeIteratorTraits
	{
		public:

		NucleotideIteratorTraits()
			:	CompositeIteratorTraits()
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<Nucleotide> >();
		}
			
		NucleotideIteratorTraits(const Composite& composite)
			:	CompositeIteratorTraits(composite)
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<Nucleotide> >();
		}
			
		NucleotideIteratorTraits(const NucleotideIteratorTraits& traits, bool /* deep */ = true)
			:	CompositeIteratorTraits(traits)
		{
		}
			
		NucleotideIteratorTraits& operator =(const NucleotideIteratorTraits& traits)
		{
			CompositeIteratorTraits::operator=(traits);
			return *this;
		}

		void resetPredicate()
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<Nucleotide> >();
		}
	};



	typedef BidirectionalIterator
		<Composite, Nucleotide, Composite::CompositeIterator, NucleotideIteratorTraits>
		NucleotideIterator;

	typedef ConstBidirectionalIterator
		<Composite, Nucleotide, Composite::CompositeIterator, NucleotideIteratorTraits>
		NucleotideConstIterator;

	typedef std::reverse_iterator<NucleotideIterator> NucleotideReverseIterator;

	typedef std::reverse_iterator<NucleotideConstIterator> NucleotideConstReverseIterator;

	IteratorWrapper(Nucleotide)
	ConstIteratorWrapper(Nucleotide)
} // namespace BALL

#endif // BALL_CORE_KERNEL_NUCLEOTIDEITERATOR_H
