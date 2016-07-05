set(SOURCES_LIST
	autoDeletable.C
	client.C
	composite.C
	embeddable.C
	enumerator.C
	factory.C
	object.C
	objectCreator.C
	moleculeObjectCreator.C
	persistenceManager.C
	preferencesObject.C
	processor.C
	property.C
	selectable.C
	textPersistenceManager.C
	timeStamp.C
	visitor.C
	molecularInformation.C
)

if(BALL_HAS_XDR)
	list(APPEND SOURCES_LIST XDRPersistenceManager.C)
endif()
