//_new_file_header


#ifndef BALL_CORE_MOLMEC_MDSIMULATION_MICROCANONICALMD_H   
#define BALL_CORE_MOLMEC_MDSIMULATION_MICROCANONICALMD_H   

#include <vector>

#include <BALL/core/molmec/mdsimulation/molecularDynamics.h>


namespace BALL 
{
	/** Microcanonical MD: A class for doing molecular dynamics simulations      
			according to the principle of a microcanonical ensemble (NVE), i.e.,
			the total energy of the system is kept constant. Numerical
			integration for new atom positions is done via the Velocity Verlet
			method.  \par
			
    	\ingroup  MDSimulation
	*/
  class BALL_EXPORT MicroCanonicalMD : public MolecularDynamics
	{

    public: 

    /** A local auxiliary class.
    */
    struct AuxFactors
		{
      double factor1,factor2; 
		}; 
    
    /** @name Constructors and Destructors.
    */
    //@{

    BALL_CREATE(MicroCanonicalMD)

    /** The default constructor with no arguments.
    */
    MicroCanonicalMD(); 

    /** This constructor expects a force field.
        The force field's options are used and no snapshots are taken.
    */
    MicroCanonicalMD(ForceField &myforcefield); 

    /** This constructor expects a force field and a snapshot-manager.
        The force field's options are used.
    */
    MicroCanonicalMD(ForceField &myforcefield, SnapShotManager *ssm); 

		/** This constructor wants a force field, a snapshot manager and new
				options.
    */
		MicroCanonicalMD(ForceField &myforcefield, SnapShotManager *ssm, 
				const Options &myoptions);

    /// Copy constructor
    MicroCanonicalMD(const MicroCanonicalMD& rhs); 

    /// The destructor
    virtual ~MicroCanonicalMD(); 

    //@}
    /** @name Assignment  
		*/
    //@{

    /// Assignment operator
    MicroCanonicalMD &operator=(const MicroCanonicalMD &rhs); 

    //@}
    /** @name Setup methods.
    */
    //@{

    /** This method does general setup things.
    */
    virtual bool setup(ForceField &myforcefield, SnapShotManager *ssm); 

    /** This method does general setup things.
    */
    virtual bool setup(ForceField &myforcefield, SnapShotManager *ssm,
				const Options &myoptions); 

    /** This method is meant for additional preparations  apart from those
        done in setup. 
    */
    virtual bool specificSetup();

    //@} 
    /** @name Accessors
    */
    //@{

    /** Choose a new time step
    */
    virtual void setTimeStep(double step); 

    /**  This method does the actual simulation stuff. 
         It runs for the indicated number of iterations.
         restart = true means that the counting of iterations is
                   continued from the previous run. 
    */
    virtual bool simulateIterations(Size number, bool restart = false);

    //@}

    protected:

    /*_ @name Protected methods 
    */
    //_@{ 

    /*_ A protected method for calculating some
        factors that are needed all the time
    */
    void calculateFactors();

    //_@}
    /*_ @name Protected Attributes
    */
    //_@{

    /*_  This vector contains special, precomputed factors 
    */
	std::vector<AuxFactors> mass_factor_;

    //_@} 

    };  // end of class MicroCanonicalMD  
  } // end of namespace BALL

#endif // BALL_CORE_MOLMEC_MDSIMULATION_MICROCANONICALMD_H
