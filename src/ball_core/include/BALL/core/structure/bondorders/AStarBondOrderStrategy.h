//_new_file_header


#ifndef BALL_CORE_STRUCTURE_BONDORDERS_ASTARBONDORDERSTRATEGY_H
#define BALL_CORE_STRUCTURE_BONDORDERS_ASTARBONDORDERSTRATEGY_H

#include <BALL/core/datatype/hashMap.h>
#include <BALL/core/structure/bondorders/bondOrderAssignment.h>
#include <BALL/core/structure/bondorders/bondOrderAssignmentStrategy.h>
#include <BALL/core/structure/bondorders/partialBondOrderAssignment.h>

#include <queue>


namespace BALL
{
	/** AStar algorithm for bond order assignment.
	 *  
	 *  This class implements an AStar approach for the bond order assignment
	 *  problem that can be used by the \link AssignBondOrderProcessor
	 *  AssignBondOrderProcessor \endlink.
	 */
	class AStarBondOrderStrategy
		: public BondOrderAssignmentStrategy
	{
		public:
			/** @name Constant Definitions
			*/
			//@{
			/// Option names
			struct BALL_EXPORT Option
			{
				/**	heuristic defining the tightness of the search critria 
				 * @see Option::Heuristic::SIMPLE
				 * @see Option::Heuristic::MEDIUM
				 * @see Option::Heuristic::TIGHT
				*/
				static const char* HEURISTIC;
			};

			struct BALL_EXPORT Default
			{
				static const String HEURISTIC;
			};

			struct BALL_EXPORT Heuristic
			{
				static const String SIMPLE;
				static const String MEDIUM;
				static const String TIGHT;
			};
			//@}

			AStarBondOrderStrategy(AssignBondOrderProcessor* parent);

			virtual ~AStarBondOrderStrategy();

			virtual void clear();
			virtual void init();

			virtual bool readOptions(const Options& options);
			virtual void setDefaultOptions();

			virtual boost::shared_ptr<BondOrderAssignment> computeNextSolution();

		protected:



			/// The chosen heuristic
			PartialBondOrderAssignment::HEURISTIC_INDEX heuristic_index_;

			std::priority_queue<PartialBondOrderAssignment> queue_;

			/// The priority queue. 
			// The current number of node expansions. 
			// step_ + queue_.size() gives the number of touched nodes.
			int step_;
	};

}

#endif // BALL_CORE_STRUCTURE_BONDORDERS_ASTARBONDORDERSTRATEGY_H
