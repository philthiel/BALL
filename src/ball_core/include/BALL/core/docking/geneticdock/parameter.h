//_new_file_header


#ifndef BALL_CORE_DOCKING_GENETICDOCK_PARAMETER_H
#define BALL_CORE_DOCKING_GENETICDOCK_PARAMETER_H

#include <vector>

#include <BALL/core/maths/quaternion.h>


namespace BALL
{

  class BALL_EXPORT GenericParameter
  {
  public:

    /** standard constructor
     */
    GenericParameter();

    /** copy constructor
     */
    GenericParameter(const GenericParameter&);

    /** destructor
     */
    virtual ~GenericParameter();

    /** assignment operator
     */
    const GenericParameter& operator = (const GenericParameter&);

    /** get parameter name
     */
    virtual String getName();

  protected:

    /** parameter name
     */
    String name_;

  };


  class BALL_EXPORT DoubleParameter: public GenericParameter
  {
  public:
    /** standard constructor
     */
    DoubleParameter();

    /** copy constructor
     */
    DoubleParameter(const DoubleParameter&);

    /** destructor
     */
    virtual ~DoubleParameter();

    /** assignment operator
     */
    const DoubleParameter& operator = (const DoubleParameter&);

    /** parameter values
     */
	std::vector<double> values;

  };


  class BALL_EXPORT QuaternionParameter: public GenericParameter
  {
  public:
    /** standard constructor
     */
    QuaternionParameter();

    /** copy constructor
     */
    QuaternionParameter(const QuaternionParameter&);

    /** destructor
     */
    virtual ~QuaternionParameter();

    /** assignment operator
     */
    const QuaternionParameter& operator = (const QuaternionParameter&);

    /** parameter value
     */
    Quaternion quat;
  };
}

#endif // BALL_CORE_DOCKING_GENETICDOCK_PARAMETER_H
