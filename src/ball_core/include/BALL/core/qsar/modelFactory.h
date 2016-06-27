//_new_file_header


#ifndef BALL_CORE_QSAR_MODELFACTORY_H
#define BALL_CORE_QSAR_MODELFACTORY_H

#include <BALL/core/concept/factory.h>
#include <BALL/core/qsar/Model.h>
#include <BALL/core/qsar/QSARData.h>


namespace BALL
{
	namespace QSAR
	{
		//typedef Model* (*CreateMethod) (const QSARData& q);
		
		/** Factory class.
		The factory class is used to create objects of the various regression / classification Models it was parameterized with. */
		template <typename T>
		class ModelFactory
		{
			public:
			
			static T* create(const QSARData& q)
			{
				return new T(q);
			}
			
			static T* createKernel1(const QSARData& q, int k, double p1, double p2)
			{
				return new T(q,k,p1,p2);
			}
			
			static T* createKernel2(const QSARData& q, String s1, String s2)
			{
				return new T(q,s1,s2);
			}
		};
	}
}

#endif // BALL_CORE_QSAR_MODELFACTORY_H
