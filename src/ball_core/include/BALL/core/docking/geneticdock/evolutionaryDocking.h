//_new_file_header


#ifndef BALL_CORE_DOCKING_GENETICDOCK_EVOLUTIONARYDOCKING_H
#define BALL_CORE_DOCKING_GENETICDOCK_EVOLUTIONARYDOCKING_H

#include <BALL/core/datatype/regularData3D.h>
#include <BALL/core/docking/common/dockingAlgorithm.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/scoring/common/scoringFunction.h>


namespace BALL
{
  class GeneticAlgorithm;

  class DockProblem;


  /**
     class EvolutionaryDocking
     This class is derived from class DockingAlgorithm.
     small ligand docking algorithm via a genetic Algorithm.
  */
  class BALL_EXPORT EvolutionaryDocking : public DockingAlgorithm
    {
    public:

     struct Option
      {
	static const String MAX_ITERATIONS;
	static const String POPULATION_NUMBER;
	static const String INITIAL_POPULATION;
	static const String POPULATION;
	static const String SURVIVORS;
	static const String MUTATION_RATE;
	static const String MUTATION_SAVE;
	static const String CONV_ITERATIONS;
	static const String CONV_VALUE;
	static const String CONV_START;
	static const String BEST_NUM;
	static const char* SCORING_TYPE;
      };

      struct Default
      {
	static const int MAX_ITERATIONS;
	static const int POPULATION_NUMBER;
	static const int INITIAL_POPULATION;
	static const int POPULATION;
	static const int SURVIVORS;
	static const double MUTATION_RATE;
	static const int MUTATION_SAVE;
	static const int CONV_ITERATIONS;
	static const double CONV_VALUE;
	static const int CONV_START;
	static const int BEST_NUM;
	static const String SCORING_TYPE;
      };


	EvolutionaryDocking(System &system1, System &system2, Options& new_options);

	EvolutionaryDocking(System& receptor, System& ligand, String config_file);

      /** destructor
       */
      ~EvolutionaryDocking();

      /** The setup routines.
       */
      virtual void setup(System& ligand, BALL::ScoringFunction* sf, Options& new_options);

      virtual void setup(System& ligand, BALL::ScoringFunction* sf);

      void setup(System& receptor, System& ligand, Options& new_options);

      /** Start the main loop of the algorithm.
       */
      void start();

      /** docks the given ligand and returns the score for the best conformation */
      double dockLigand(AtomContainer& ligand, bool verbose = 0);

      /** return the overall docking progress as a percentage
       */
      float getProgress() const;

      /** true if new ligand position has to be drawn
       */
      bool redraw();

      Vector3& getReferenceLigandCenter();

      /** return ranked conformations.
       */
   //   ConformationSet getConformationSet(Index total_number = 0);

      /** stores the default options of this algorithms in the given Option object */
      static void getDefaultOptions(Options& options);


    protected:

     // virtual const AtomContainer& getIntermediateResult_()
	//throw();

      /** Free all allocated memory and destroys the options and results
       */
      void destroy_();

      void applyBestConformation();

      /** optimization method
       */
      GeneticAlgorithm* ga_;

      /** mapping class for docking
       */
      DockProblem* dp_;

      /** the geometrical center of the reference ligand */
      Vector3 reference_center_;

    };
}

#endif // BALL_CORE_DOCKING_GENETICDOCK_EVOLUTIONARYDOCKING_H
