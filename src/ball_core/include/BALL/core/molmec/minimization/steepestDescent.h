//_new_file_header


#ifndef BALL_CORE_MOLMEC_MINIMIZATION_STEEPESTDESCENT_H
#define BALL_CORE_MOLMEC_MINIMIZATION_STEEPESTDESCENT_H

#include <BALL/core/molmec/minimization/energyMinimizer.h>
#include <BALL/core/molmec/minimization/lineSearch.h>


namespace BALL 
{
	/** A minimizer for geometry optimization based on steepest descent steps.
	 *  \ingroup  MolmecEnergyMinimizer
	 */
	class BALL_EXPORT SteepestDescentMinimizer 
		: public EnergyMinimizer
	{
		
		public:
			
			/** @name Constructors and Destructors
			*/
			//@{
			
			BALL_CREATE(SteepestDescentMinimizer)
			
			/** Default constructor.
			*/
			SteepestDescentMinimizer();
			
			/** Constructor.
			*/
			SteepestDescentMinimizer(ForceField& force_field);
			
			/** Constructor.
			*/
			SteepestDescentMinimizer(ForceField& force_field,SnapShotManager *ssm);
			
			/** Constructor.
			*/
			SteepestDescentMinimizer(ForceField& force_field, const Options& options);
			
			/** Constructor.
			*/
			SteepestDescentMinimizer(ForceField& force_field, SnapShotManager* ssm, const Options& options);
			
			/** Copy constructor
			*/
			SteepestDescentMinimizer(const SteepestDescentMinimizer& minimizer);
			
			/** Destructor.
			*/
			virtual ~SteepestDescentMinimizer();
			
			//@}
			/** @name Assignments
			*/
			//@{
			
			/** Assignment operator
			*/
			const SteepestDescentMinimizer&	operator = (const SteepestDescentMinimizer& minimizer);
			
			//@}
			/** @name Setup methods
			*/
			//@{
			
			/** Specific setup
			*/
			virtual bool specificSetup();
			
			//@}
			/** @name Accessors
			 */
			//@{
			
			/** Minimize the energy of the system using steepest descent steps.
			 *  This method executes at most <tt>iterations</tt> minimization steps.
			 *  If the number of iterations is not given, the number specified in the
			 *  options is taken.
			 *  @param iterations the maximum number of iterations
			 *  @param resume <b>true</b> to resume a previous run
			 *  @see EnergyMinimizer::minimize
			 */
			virtual bool minimize(Size steps = 0, bool resume = false);
			
			/** Find the next step.
			 *  First, this method calls updateDirection. Second, it performs a line search
			 *  along the calculated direction afterwards.
			 *  @return double  \f$\geq 0\f$ if the line search found an acceptable solution, otherwise -1.
			 *  @see EnergyMinimizer::findStep
			 */
			virtual double findStep();
			
			/** Update the search direction.
			 *  This algorithm uses only steepest descent searches.
			 *  Therefore, updateDirection only assigns direction to the last gradient
			 *  computed.
			 */
			virtual void updateDirection();
			
		protected:
			
			//@}
			/** @name Protected Attributes
			 */
			//@{
			
			/** The line search minimizer.
			 *  This member is used to perform the line search in findStep
			 */
			LineSearch line_search_;
			//@}
			
	};
} // namespace BALL

#endif // BALL_CORE_MOLMEC_MINIMIZATION_STEEPESTDESCENT_H
