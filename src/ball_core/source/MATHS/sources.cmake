set(SOURCES_LIST
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
	plane3.C
	piecewiseFunction.C
	piecewisePolynomial.C
	quaternion.C
	randomNumberGenerator.C
	simpleBox3.C
	sphere3.C
	surface.C
	vector2.C
	vector3.C
	vector4.C
)

if(BALL_HAS_FFTW)
	list(APPEND SOURCES_LIST FFT1D.C FFT2D.C FFT3D.C)
endif()

#ADD_BALL_PARSER_LEXER("MATHS" "parsedFunction" "ParsedFunction")
