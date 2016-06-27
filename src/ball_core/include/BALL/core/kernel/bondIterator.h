//_new_file_header


#ifndef BALL_CORE_KERNEL_BONDITERATOR_H
#define BALL_CORE_KERNEL_BONDITERATOR_H

#include <BALL/core/kernel/atom.h>


namespace BALL
{
	/** @name Typedefs for the various BondIterators
    	\ingroup  KernelIterators
	*/
	//@{

	/** A mutable iterator for atom bonds.
	*/
	typedef Atom::BondIterator             AtomBondIterator;

	/** A constant iterator for atom bonds.
	*/
	typedef Atom::BondConstIterator        AtomBondConstIterator;

	/** A mutable reverse iterator for atom bonds.
	*/
	typedef Atom::BondReverseIterator      AtomBondReverseIterator;

	/** A constant reverse iterator for atom bonds.
	*/
	typedef Atom::BondConstReverseIterator AtomBondConstReverseIterator;

	//@}
}

#endif // BALL_CORE_KERNEL_BONDITERATOR_H
