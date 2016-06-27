//_new_file_header


#ifndef BALL_CORE_DOCKING_GENETICDOCK_DOCKPROBLEM_H
#define BALL_CORE_DOCKING_GENETICDOCK_DOCKPROBLEM_H

#include <vector>
#include <string>

#include <BALL/core/docking/common/conformationSet.h>
#include <BALL/core/docking/geneticdock/evolutionaryDocking.h>
#include <BALL/core/docking/geneticdock/geneticAlgorithm.h>
#include <BALL/core/docking/geneticdock/parameter.h>
#include <BALL/core/docking/geneticdock/rotateBonds.h>
#include <BALL/core/kernel/molecule.h>
#include <BALL/core/kernel/protein.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/maths/matrix44.h>
#include <BALL/core/maths/quaternion.h>
#include <BALL/core/maths/vector3.h>
#include <BALL/core/scoring/common/scoringFunction.h>


namespace BALL
{

  class BALL_EXPORT DockProblem
    {
    public:
      /** constructor
       */
      DockProblem();

      /** constructor
       */
      DockProblem(AtomContainer& sys_lig, BALL::ScoringFunction* sf,
		  EvolutionaryDocking* docker, bool post_dock_optimization);


      /** destructor
       */
      virtual ~DockProblem();


      virtual void setup(AtomContainer& sys_lig);


      /** calculate fitness score for one individual
       */
      virtual double calculate();

      /** move molecule according to vectors double_parameter_ and quaternion_parameter_, which are set by GeneticAlgorithm::calculate() */
      void move();

      /** true if best solution has changed
       */
      bool redraw();

      AtomContainer* getLigand();


      void connectTo(GeneticAlgorithm* opt);


    protected:

      EvolutionaryDocking* docker_;

      DoubleParameter double_parameter_;

      QuaternionParameter quaternion_parameter_;

      /** pointer to ligand molecule
       */
      AtomContainer* ligand_, *draw_ligand_;

      /** variables to store position and extentions of ligand and receptor
       */
      Vector3 t_origin_, t_extension_;

      Vector3 binding_pocket_center_;

      /**  calculate conformation score
       */
      BALL::ScoringFunction* scoring_function_;

      /** Vector to restore the position values of the ligand
       */
      std::vector<Vector3 > ligand_positions_;

      /** rotate bonds class
       */
      RotateBonds* rb_;



      /** set all rotable molecules to original positions
       */
      void restore();

      /** amber options
       */
      Options opt_;

      bool redraw_;

		bool post_dock_optimization_;

    };
}

#endif // BALL_CORE_DOCKING_GENETICDOCK_DOCKPROBLEM_H
