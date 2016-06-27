//_new_file_header


#ifndef BALL_CORE_KERNEL_MOLECULEITERATOR_H
#define BALL_CORE_KERNEL_MOLECULEITERATOR_H

#include <BALL/core/concept/stdIteratorWrapper.h>
#include <BALL/core/kernel/iterator.h>
#include <BALL/core/kernel/predicate.h>


namespace BALL 
{
	/** MoleculeIteratorTratis_
	 		\ingroup KernelIterators
	*/
	class BALL_EXPORT MoleculeIteratorTraits
		: public CompositeIteratorTraits
	{
		public:
		
		MoleculeIteratorTraits()
			:	CompositeIteratorTraits()
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<Molecule> >();
		}
			
		MoleculeIteratorTraits(const Composite& composite)
			:	CompositeIteratorTraits(composite)
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<Molecule> >();
		}
			
		MoleculeIteratorTraits(const MoleculeIteratorTraits& traits, bool /* deep */ = true)
			:	CompositeIteratorTraits(traits)
		{
		}
			
		MoleculeIteratorTraits &operator = (const MoleculeIteratorTraits& traits)
		{
			CompositeIteratorTraits::operator=(traits);
			return *this;
		}

		void resetPredicate()
		{
			predicate_ = &RTTI::getDefault<KernelPredicate<Molecule> >();
		}
	};


	///
	typedef BidirectionalIterator
		<Composite, Molecule, Composite::CompositeIterator, MoleculeIteratorTraits>
		MoleculeIterator;

	///
	typedef ConstBidirectionalIterator
		<Composite, Molecule, Composite::CompositeIterator, MoleculeIteratorTraits>
		MoleculeConstIterator;

	///
	typedef std::reverse_iterator<MoleculeIterator> MoleculeReverseIterator;
	
	///
	typedef std::reverse_iterator<MoleculeConstIterator> MoleculeConstReverseIterator;

	IteratorWrapper(Molecule)
	ConstIteratorWrapper(Molecule)
} // namespace BALL

#endif // BALL_CORE_KERNEL_MOLECULEITERATOR_H
