//_new_file_header


#include <BALL/core/structure/RDFIntegrator.h>

#include <BALL/core/common/logStream.h>

using namespace std;


namespace BALL
{
	RDFIntegrator::RDFIntegrator()
		
		:	rdf_(),
			valid_(false)
	{
	}


	RDFIntegrator::RDFIntegrator(const RDFIntegrator& integrator)
		
		: rdf_(integrator.rdf_),
			valid_(false)
	{
	}
	

	RDFIntegrator::RDFIntegrator(const RadialDistributionFunction& rdf)
		
		: rdf_(rdf),
			valid_(false)
	{
	}


	RDFIntegrator::~RDFIntegrator()
		
	{
		clear();

		valid_ = false;
	}


	void RDFIntegrator::clear()
		
	{
		rdf_.clear();
	}


	void RDFIntegrator::setRDF(const RadialDistributionFunction& rdf)
		
	{
		rdf_ = rdf;
	}


	const RadialDistributionFunction& RDFIntegrator::getRDF() const 
		
	{
		return rdf_;
	}


	const RDFIntegrator& RDFIntegrator::operator = (const RDFIntegrator& integrator)
		
	{
		rdf_ = integrator.rdf_;
		return *this;
	}


	bool RDFIntegrator::operator == (const RDFIntegrator& integrator) const
		
	{
		return (rdf_ == integrator.rdf_);
	}


	bool RDFIntegrator::isValid() const
		
	{
		return valid_;
	}


	double RDFIntegrator::operator () (double /* x */) const
		
	{
		Log.error() << "RDFIntegrator::operator () (double): "
								<< "This method should not be called!" << endl;
		return 0.0;
	}
}
