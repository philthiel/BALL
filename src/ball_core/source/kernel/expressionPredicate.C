//_new_file_header


#include <BALL/core/kernel/expressionPredicate.h>


namespace BALL
{

	ExpressionPredicate::ExpressionPredicate() 
		: UnaryPredicate<Atom>(),
			argument_("")
	{
	}


	ExpressionPredicate::ExpressionPredicate
		(const ExpressionPredicate& predicate) 
		:	UnaryPredicate<Atom>(predicate),
			argument_(predicate.argument_)
	{
	}


	ExpressionPredicate::ExpressionPredicate(const String& argument) 
		:	UnaryPredicate<Atom>(),
			argument_(argument)
	{
	}


	ExpressionPredicate::~ExpressionPredicate() 
	{
		clear();
	}


	ExpressionPredicate& ExpressionPredicate::operator = (const ExpressionPredicate& predicate) 
	{
		UnaryPredicate<Atom>::operator = (predicate);
		argument_ = predicate.argument_;

		return *this;
	}


	void ExpressionPredicate::clear() 
	{
		argument_ = "";
	}


	bool ExpressionPredicate::operator == (const ExpressionPredicate& predicate) const 
	{
		return (argument_ == predicate.argument_);
	}


	bool ExpressionPredicate::operator () (const Atom& /* atom */) const 
	{
		return true;
	}


	void ExpressionPredicate::setArgument(const String& args) 
	{
		argument_ = args;
	}


	const String& ExpressionPredicate::getArgument() const 
	{
		return argument_;
	}

}
