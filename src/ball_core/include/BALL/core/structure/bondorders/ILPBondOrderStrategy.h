//_new_file_header


#ifndef BALL_CORE_STRUCTURE_BONDORDERS_ILPBONDORDERSTRATEGY_H
#define BALL_CORE_STRUCTURE_BONDORDERS_ILPBONDORDERSTRATEGY_H

#include <BALL/core/structure/bondorders/bondOrderAssignment.h>
#include <BALL/core/structure/bondorders/bondOrderAssignmentStrategy.h>

// forward declaration for lp_solve
struct _lprec;
typedef struct _lprec lprec;


namespace BALL
{
	/** ILP algorithm for bond order assignment.
	 *  
	 *  This class implements an Integer Linear Programming approach 
	 *  for the bond order assignment problem that can be used by 
	 *  the \link AssignBondOrderProcessor AssignBondOrderProcessor \endlink.
	 */
	class ILPBondOrderStrategy
		: public BondOrderAssignmentStrategy
	{
		public:
			ILPBondOrderStrategy(AssignBondOrderProcessor* parent);
			virtual ~ILPBondOrderStrategy();

			virtual void clear();
			virtual void init();

			virtual bool readOptions(const Options& options);
			virtual void setDefaultOptions();

			virtual boost::shared_ptr<BondOrderAssignment> computeNextSolution();

		protected:
			bool valid_;

			// Vector for mapping from variable indices onto free bonds in the
			// order used by the ILP
			std::vector<Bond*> index_to_free_bond_;

			// number of bond variables in the ILP
			Position number_of_free_bonds_;

			// Constant penalty (fixed bonds)
			float const_penalty_;

			// flag indicating whether constraints need to be added
			bool first_solution_;

			// the ilp
			lprec* ilp_;
	};
}

#endif // BALL_CORE_STRUCTURE_BONDORDERS_ILPBONDORDERSTRATEGY_H
