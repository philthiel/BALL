//_new_file_header


#ifndef BALL_CORE_STRUCTURE_PEPTIDECAPPROCESSOR_H
#define BALL_CORE_STRUCTURE_PEPTIDECAPPROCESSOR_H

#include <BALL/core/concept/composite.h>
#include <BALL/core/kernel/chain.h>
#include <BALL/core/kernel/residue.h>
#include <BALL/core/maths/vector3.h>
#include <BALL/core/structure/atomBijection.h>


namespace BALL
{

  /** Processor for adding caps to proteins
		\ingroup StructureMiscellaneous
   */

  /** \brief This processor adds ACE-N and NME-C caps to proteins.
  */

	class BALL_EXPORT PeptideCapProcessor
		: public UnaryProcessor<Chain>
	{
		public:

		/**	@name	Constructors */
		//@{
				/// Default constructor
				PeptideCapProcessor();
		//@}

		/**	@name Processor-related methods */
		//@{
				/// ()-operator
				virtual Processor::Result operator() (Chain& chain);
		//@}

		protected:

			//function to compute the distance of the cap atoms and the last residue
			float computeDistance(std::vector<Atom*>& a, std::vector<Atom*>& b);

			//function to optimize cap position by rotation
			void optimizeCapPosition(Chain& chain, bool start);
	};

} //namespace BALL

#endif // BALL_CORE_STRUCTURE_PEPTIDECAPPROCESSOR_H
