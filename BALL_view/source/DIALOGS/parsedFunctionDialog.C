// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
#include <BALL_view/DIALOGS/parsedFunctionDialog.h>
#include <BALL_view/WIDGETS/scene.h>
#include <BALL_view/KERNEL/mainControl.h>
#include <BALL_view/KERNEL/stage.h>

#include <QtGui/QPushButton>
#include <QtGui/QLineEdit> 

namespace BALL
{
	namespace VIEW
	{

ParsedFunctionDialog::ParsedFunctionDialog( QWidget* parent,  const char* name)
    : QDialog(parent),
			Ui_ParsedFunctionDialogData()
{
	setupUi(this);
	setObjectName(name);
	
  // signals and slots connections
  connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
  connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );

	show();
}

ParsedFunctionDialog::~ParsedFunctionDialog()
{
 // no need to delete child widgets, Qt does it all for us
}

// NAMESPACE
} }
