//_new_file_header


#ifndef BALL_CORE_DOCKING_GENETICDOCK_GENES_H
#define BALL_CORE_DOCKING_GENETICDOCK_GENES_H


#include <BALL/core/maths/quaternion.h>

#include <random>
#include <vector>


namespace BALL
{
  //class RandomNumberGenerator;

  /** pure virtual base class
   */
  class BALL_EXPORT GenericGene
  {
  public:

    /** destructor
     */
    virtual ~GenericGene(){};

    /** mate two genes
     */
    virtual GenericGene* mate(GenericGene* gg) = 0;

    /** mutate gene
     */
    virtual void mutate() = 0;

    /** clone method
     */
    virtual GenericGene* clone() = 0;

    /** set gene to random value
     */
    virtual void randomize() = 0;

    /** initilize random number generator
     */
	//static void initializeRNG();

  protected:

    /** random number generator for all genes
     */
	//static RandomNumberGenerator rng_;
	static std::mt19937 mersenne_twister;

	static std::uniform_real_distribution<double> rand_double_0_1;
  };

  /** gene with an arbitrary number of double values
   */
  class BALL_EXPORT DoubleGene: public GenericGene
  {
  public:

    /** constructor
     */
    DoubleGene();

    /** destructor
     */
    virtual ~DoubleGene();

    /** constructor, i double values
     */
    DoubleGene(Size i);

    /** mating method
     */
    virtual GenericGene* mate(GenericGene* gg);

    /** mutation method
     */
    virtual void mutate();

    /** get vector of values
     */
    std::vector<double> getValues();

    /** set values
     */
    void setValue(std::vector<double> v);

    /** clone method
     */
    virtual GenericGene* clone();

    /** randomize values
     */
    void randomize();

  private:

    /** genes values
     */
    std::vector<double> values_;
  };


  /** gene with one quaternion value
   */
  class BALL_EXPORT QuaternionGene: public GenericGene
  {
  public:

    /** constructor
     */
    QuaternionGene();

    /** destructor
     */
    virtual ~QuaternionGene();

    /** mating method
     */
    virtual GenericGene* mate(GenericGene* gg);

    /** mutation method
     */
    virtual void mutate();

    /** returns quaternion vaue
     */
    Quaternion getValue();

    /** clone method
     */
    virtual GenericGene* clone();

    /** randomize quaternion
     */
    void randomize();

  private:

    /** quaternion value
     */
    Quaternion quat_;

  };


}

#endif // BALL_CORE_DOCKING_GENETICDOCK_GENES_H
