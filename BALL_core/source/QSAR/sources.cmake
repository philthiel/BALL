# Set the source group name
SET(GROUP QSAR)

# List all filenames of this group here
SET(SOURCES_LIST
	allModel.C
	aromaticityProcessor.C
	automaticModelCreator.C
	bayesModel.C
	classificationModel.C
	classificationValidation.C
	configIO.C
	connectivityBase.C
	connectivityDescriptors.C
	descriptor.C
	exception.C
	featureSelection.C
	gpModel.C
	kernel.C
	kernelModel.C
	knnModel.C
	kpcrModel.C
	kplsModel.C
	latentVariableModel.C
	ldaModel.C
	linearModel.C
	logitModel.C
	mlrModel.C
	Model.C
	modelFactory.C
	nBModel.C
	nonlinearModel.C
	oplsModel.C
	partialChargeBase.C
	partialChargeDescriptors.C
	partialChargeProcessor.C
	pcrModel.C
	plsModel.C
	QSARData.C
	registry.C
	regressionModel.C
	regressionValidation.C
	ringPerceptionProcessor.C
	rrModel.C
	simpleBase.C
	simpleDescriptors.C
	snBModel.C
	statistics.C
	surfaceBase.C
	surfaceDescriptors.C
	svmModel.C
	svrModel.C
	validation.C
)

IF(BALL_HAS_GSL)
	LIST(APPEND SOURCES_LIST fitModel.C)
ENDIF()

IF(BALL_HAS_LIBSVM)
	LIST(APPEND SOURCES_LIST libsvmModel.C)
ENDIF()
