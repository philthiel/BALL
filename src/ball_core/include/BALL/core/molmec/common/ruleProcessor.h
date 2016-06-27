//_new_file_header


#ifndef BALL_CORE_MOLMEC_COMMON_RULEPROCESSOR_H
#define BALL_CORE_MOLMEC_COMMON_RULEPROCESSOR_H

#include <BALL/core/concept/processor.h>
#include <BALL/core/molmec/common/ruleEvaluator.h>


namespace BALL 
{
	/**	Rule Processor class.
	 * Molecular Mechanics: rule-based assignment of properties (typenames, charges, radii, etc.)
    	\ingroup  MolmecAssignment
	*/
	class BALL_EXPORT RuleProcessor
		:	public UnaryProcessor<Atom>
	{
		public:

		BALL_CREATE(RuleProcessor)

		/**	Constructors and Destructors
		*/
		//@{

		/**	Default constructor
		*/
		RuleProcessor();
			
		/**	Detailed constructor
		*/
		RuleProcessor(INIFile& file, const String& prefix);
			
		/**	Copy constructor
		*/
		RuleProcessor(const RuleProcessor& rule_processor);

		/**	Destructor
		*/
		~RuleProcessor();

		/**
		*/
		void clear();
			
		/**
		*/
		void destroy();			

		//@}
		/**	@name	Accessors
		*/
		//@{

		/**
		*/
		bool initialize(INIFile& file, const String& prefix);

		//@}
		/**	@name	Assignment
		*/
		//@{
			
		/**
		*/
		const RuleProcessor& operator = (const RuleProcessor& rule_processor);

		/**	
		*/
		void set(const RuleProcessor& rule_processor);

		//@}
		/**	@name Processor related methods
		*/
		//@{

		/**
		*/
		virtual bool start();

		/**
		*/
		virtual bool finish();

		/** 
		*/
		String evaluate(const Atom& atom);

		//@}
		/**	@name Debugging and Diagnostics
		*/
		//@{

		///
		bool isValid() const;
		
		///
		void dump(std::ostream& s = std::cout) const;

		//@}

		protected:

		//_
		RuleEvaluator	evaluator_;

		//_ 
		bool					valid_;
	};
} // namespace BALL


#endif // BALL_CORE_MOLMEC_COMMON_RULEPROCESSOR_H
