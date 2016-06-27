//_new_file_header


#ifndef BALL_CORE_XRAY_CRYSTALGENERATOR_H
#define BALL_CORE_XRAY_CRYSTALGENERATOR_H

#include <BALL/core/datatype/regularData3D.h>
#include <BALL/core/datatype/string.h>
#include <BALL/core/kernel/atomContainer.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/maths/box3.h>
#include <BALL/core/structure/geometricProperties.h>
#include <BALL/core/structure/geometricTransformations.h>
#include <BALL/core/xray/crystalInfo.h>


namespace BALL
{
	/** CrystalGenerator Class
	 \ingroup XRAY
	*/
	class BALL_EXPORT CrystalGenerator
	{
		public:


			/** @name Enums
			*/
			//@{

			/**
			*/
			enum CellType
			{
				NCS_ASU 	= 0,
				ASU     	= 1,
				UNITCELL	= 2
			};

			/** Option Names
			 */
			struct BALL_EXPORT Option
			{
				/** The file name for the space group to symmetry operations mappings file
				 */
				static const String SPACE_GROUP_FILE;
			};
			
			/** Default Names
			 */
			struct BALL_EXPORT Default
			{
				/** The default filename for the space group mappings file
				 */
				static const String SPACE_GROUP_FILE;
			};

			/** @name constructors and Destructors
			*/
			//@{
			/**	Default Constructor.
			 		This methods creates a new CrystalGenerator object
				
			*/
			CrystalGenerator();
			
			/**	Copy Constructor.
			 		Creates a new CrystalGenerator object from another
					@param	cg	the CrystalGenerator to be copied from
				
			*/
			CrystalGenerator(const CrystalGenerator& cg);

			/**	Destructor.
			*/
			~CrystalGenerator();
			//@}

			///
			void setSpaceGroupFilename(String& filename){filename_ = filename;};	
			
			///
			const String& getSpaceGroupFilename() const {return filename_;};	
			void setCrystalInfo(boost::shared_ptr<CrystalInfo> ci_ptr);
			void setSystem(System* system_ptr);	

			std::list<System*> generatePacking(Index a_loweridx, Index a_upperidx, Index b_loweridx, Index b_upperid, Index c_loweridx, Index c_upperid);	

			System* generateUnitCell(Index a, Index b, Index c);	
			System* generateUnitCell();	
			System* generateAsymmetricUnit();	
			std::list<System*> generateSymMoleculesWithinDistance(float angstrom);	
			
			Box3 getUnitCellBox(Index a, Index b, Index c);

		protected:
			
			bool buildUnitCell_();	
			bool buildASU_();
			bool correctASUPositions_(System* raw_cell);
			
			GeometricCenterProcessor center_processor_;
			TransformationProcessor transformer_;
			
			System* system_;
			
			System* asu_;
			System* unitcell_;
			boost::shared_ptr<CrystalInfo> ci_ptr_;
			String filename_;
	};
}	// namespace BALL

#endif // BALL_CORE_XRAY_CRYSTALINFO_H
