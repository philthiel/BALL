# Set the source group name
SET(GROUP MATHS)

# List all filenames of this group here
SET(SOURCES_LIST
	analyticalGeometry.C
	angle.C
	box3.C
	circle3.C
	cubicSpline1D.C
	cubicSpline2D.C
	function.C
	line3.C
	matrix44.C
	parsedFunction.C
	piecewiseFunction.C
	piecewisePolynomial.C
	plane3.C
	quaternion.C
	randomNumberGenerator.C
	simpleBox3.C
	sphere3.C
	surface.C
	vector2.C
	vector3.C
	vector4.C
)

IF(BALL_HAS_FFTW)
	SET(SOURCES_LIST ${SOURCES_LIST} FFT1D.C FFT2D.C FFT3D.C)
ENDIF()

SET(PARSER_LEXER_LIST
	parsedFunction
)
