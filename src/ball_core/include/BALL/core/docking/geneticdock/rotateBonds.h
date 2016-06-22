// ----------------------------------------------------
// $Maintainer: Marcel Schumann $
// $Authors: Jan Fuhrmann, Marcel Schumann $
// ----------------------------------------------------

#ifndef BALL_DOCKING_GENETICDOCK_ROTATEBONDS_H
#define BALL_DOCKING_GENETICDOCK_ROTATEBONDS_H

#include <BALL/core/kernel/system.h>
#include <BALL/core/kernel/atom.h>
#include <BALL/core/datatype/hashSet.h>
#include <BALL/core/kernel/protein.h>
#include <BALL/core/docking/common/staticLigandFragment.h>

#include <vector>



namespace BALL
{
  class RotateBond;

  class BALL_EXPORT RotateBonds
    {
    public:

      RotateBonds(const vector<Bond*>* rotatable_bonds);

      /** copy constructor
       */
      RotateBonds(const RotateBonds& rb);

      /** assignment operator
       */
      RotateBonds& operator = (const RotateBonds& rb);

      /** default destructor
       */
      ~RotateBonds();

      /** rotate all rotable bonds according to vec
       */
      void rotate(std::vector<double> vec);

      /** returns number of rotable bonds
       */
      int numberBonds();

    private:

      /** vector to store all rotable bonds
       */
      std::vector<RotateBond*> bonds_;

    };
}



#endif /* BALL_DOCKING_GENETICDOCK_ROTATEBONDS_H */
