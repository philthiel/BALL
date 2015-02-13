# Set the source group name
SET(GROUP RENDERING/RENDERERS)

# List all filenames of this group here
SET(SOURCES_LIST
	glRenderer.C
	POVRenderer.C
	raytracingRenderer.C
	renderer.C
	STLRenderer.C
	tilingRenderer.C
	VRMLRenderer.C
	XML3DRenderer.C
)

IF(BALL_HAS_RTFACT)
	SET(SOURCES_LIST ${SOURCES_LIST} rtfactRenderer.C)
ENDIF()
