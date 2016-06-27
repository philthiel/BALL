//_new_file_header


#ifndef BALL_CORE_KERNEL_EXPRESSIONTREE_H
#define BALL_CORE_KERNEL_EXPRESSIONTREE_H

#include <BALL/core/kernel/expressionPredicate.h>

#include <list>


namespace BALL
{

	/** Expression tree class.
			Represents the logical tree of an Expression. This is the backend of
			Expression.
			 \par
			
			@see Expression
		 	\ingroup KernelMiscellaneous 
	*/
	class BALL_EXPORT ExpressionTree
	{
		public:

		BALL_CREATE(ExpressionTree)

		/**	@name	Type Definitions
		*/
		//@{

		/** The type of an expression node in the tree.
				The type determines how a node is to be interpreted.
		*/
		enum Type
		{	
			/// The node is invalid.
			INVALID = 0,
			/// The node is a leaf.
			LEAF,
			/// The node is a logical OR conjunction.
			OR,
			/// The node is a logical AND conjunction.
			AND
		};
		//@}

		/**	@name	Constructors and Destructor
		*/
		//@{
			
		/**	Default constructor.
				Create an empty expression node. The node's type is set to INVALID,
				<tt>negate_</tt> is set to <b>false</b>, the internal predicate is set
				to 0, and the list of children is empty.
		*/
		ExpressionTree();
			
		/** Copy constructor. Note that this copy constructor does not copy
				predicates but only stores pointers to them.
		 */
		ExpressionTree(const ExpressionTree& tree);

		/**	Detailed constructor.
				Create an expression node representing a leaf, i.e., a 
				predicate.
				@param	predicate the node's predicate
				@param	negate set to <b>true</b> if the node's predicate should be
								negated
		*/
		ExpressionTree(ExpressionPredicate* predicate, bool negate = false);

		/**
		*/
		ExpressionTree(Type type, std::list<const ExpressionTree*> children, bool negate = false);

		/**	Destructor
		*/
		virtual ~ExpressionTree();

		//@}
		/**	@name	Predicates
		*/
		//@{
		
		/** Evaluate the (sub)expression.
		*/
		virtual bool operator () (const Atom& atom) const;

		/** Equality operator 
		 */
		bool operator == (const ExpressionTree& tree) const;

		/** Inequality operator 
		 */
		bool operator != (const ExpressionTree& tree) const;

		//@}
		/**	@name	Accessors
		*/
		//@{

		/**	Set the expression node's type.
		*/
		void setType(Type type) ;

		/** Get the expression node's type 
		 */
		Type getType() const;
		
		/**	Set the expression node's negation mode.
		*/
		void setNegate(bool negate);

		/** Get the expression node's negation mode. 
		 */
		bool getNegate() const;

		/**	Set the predicate.
		*/
		void setPredicate(ExpressionPredicate* predicate);

		/**	Get the predicate. 
		 */
		ExpressionPredicate* getPredicate() const;

		/**	Append a child to the tree.
		*/
		void appendChild(const ExpressionTree* child);

		/** Get the list of children.
		*/
		const std::list<const ExpressionTree*>& getChildren() const;

		//@}
		/** @name Assignment 
		 */
		//@{

		/** Asignment operator 
		 */
		ExpressionTree& operator = (const ExpressionTree& tree);

		/** Clear method 
		 */
		virtual void clear();

		//@}
		/**	@name Debugging
		*/
		//@{
		void dump(std::ostream& is = std::cout, Size depth = 0) const;
		//@}

		
		protected:
		
		/*_ A helper function for operator == () that compares the children of
				a node.
		*/
		bool compareChildren_(const ExpressionTree& tree) const;

		/*_ The type of this node.
		*/
		Type												type_;
		
		/*_ Negation flag. If set, the value of this node will be negated.
		*/
		bool												negate_;
		
		/*_ A pointer to the predicate that this node represents.
		*/
		ExpressionPredicate*				predicate_;
		
		/*_ A list containing pointers to the children of this node. 
		*/
		std::list<const ExpressionTree*>	children_;

	};

}

#endif // BALL_CORE_KERNEL_EXPRESSIONTREE_H
