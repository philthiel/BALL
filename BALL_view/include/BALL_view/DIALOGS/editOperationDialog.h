// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#ifndef BALL_VIEW_DIALOGS_EDITOPERATIONDIALOG_H
#define BALL_VIEW_DIALOGS_EDITOPERATIONDIALOG_H

#ifndef BALL_COMMON_GLOBAL_H
# include <BALL_core/COMMON/global.h>
#endif

#ifndef BALL_VIEW_KERNEL_MODULARWIDGET_H
# include <BALL_view/KERNEL/modularWidget.h>
#endif

#ifndef BALL_VIEW_WIDGETS_SCENE_H
# include <BALL_view/WIDGETS/scene.h>
#endif

#include <BALL_view/UIC/ui_editOperationDialog.h>

namespace BALL
{
	namespace VIEW
	{
		/** Dialog for storing the undo Operations of Scene.
		 		\ingroups ViewDialogs
		*/

		class BALL_VIEW_EXPORT EditOperationDialog
			: public QDialog,
				public Ui_EditOperationDialogData,
				public ModularWidget
	  {
			Q_OBJECT

			public:
			
			BALL_EMBEDDABLE(EditOperationDialogData,ModularWidget)

			///
			EditOperationDialog(QWidget* parent = 0, const char* name = "EditOperationDialog", Qt::WFlags fl = 0);

			///
			~EditOperationDialog();
		 
		
			public slots:
				
				void undo(int number_of_undo_steps);
				void operationSelected(int operation);
				void addEditOperation(Scene::EditOperation& eo);
				
			protected:

		};
	}
}

#endif
