# Set the source group name
SET(GROUP CONCEPT)

# List all filenames of this group here
SET(SOURCES_LIST
	autoDeletable.C
	composite.C
	embeddable.C
	enumerator.C
	factory.C
	molecularInformation.C
	moleculeObjectCreator.C
	object.C
	objectCreator.C
	persistenceManager.C
	preferencesObject.C
	processor.C
	property.C
	selectable.C
	textPersistenceManager.C
	timeStamp.C
	visitor.C
)

IF(BALL_HAS_XDR)
	LIST(APPEND SOURCES_LIST XDRPersistenceManager.C)
ENDIF()

IF(BALL_HAS_ASIO)
	SET(SOURCES_LIST ${SOURCES_LIST} client.C)
ENDIF()
