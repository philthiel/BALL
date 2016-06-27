//_new_file_header


#include <BALL/core/concept/objectCreator.h>

using namespace std;


namespace BALL
{
  
	ObjectCreator::ObjectCreator()
			
		:
		init_(false),
		pm_()
	{
	}

	ObjectCreator::~ObjectCreator()
			
	{
		#ifdef BALL_DEBUG
			cout << "Destructing object " << (void *)this 
				<< " of class " << RTTI::getName<ObjectCreator>() << endl;
		#endif 
	}

	void ObjectCreator::clear()
			
	{
	}


	void ObjectCreator::initPersistenceManager(TextPersistenceManager & /* pm */)
			
	{
	}

	Composite *ObjectCreator::convertObject(PersistentObject & /* po */)
			
	{
		return (Composite *)0;
	}

	Composite *ObjectCreator::operator() (TCPIOStream& tcp_iostream)
			
	{
		// initialize the PersistenceManager only one times
		if (init_ == false)
		{
			init_ = true;

			initPersistenceManager(pm_);
		}

		// read persistent object from stream
		pm_.setIstream(tcp_iostream);
		PersistentObject*	po = pm_.readObject();
		
		// convert the object
		return convertObject(*po);
	}

} // namespace BALL
