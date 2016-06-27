//_new_file_header

#ifndef BALL_CORE_CONCEPT_FACTORY_H
#define BALL_CORE_CONCEPT_FACTORY_H


namespace BALL
{

	/** Factory class.
			The factory class is used to create objects of the type it 
			was parameterized with.
			 \par
			
	 	 \ingroup ConceptsMiscellaneous
	*/
	template <typename T>
	class Factory
	{
		public:
		
		/// Return a pointer to a new instance of T
		static T* create() { return new T; }

		/// Return a void pointer to a new instance of T
		static void* createVoid() { return (void*)new T; }

		/// Return a reference to a (pre-instantiated) default object
		static const T& getDefault() 
		{ 
			static T default_instance;
			return default_instance;
		}
	};
}

#endif // BALL_CORE_CONCEPT_FACTORY_H
