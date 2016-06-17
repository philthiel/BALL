# --------------------------------------------------------------------------
# BALL: Biochemical ALgorithms Library
#       A C++ framework for molecular modeling and structural bioinformatics
# --------------------------------------------------------------------------
#
# Copyright (C) 2016 the BALL team:
# - Andreas Hildebrandt (andreas.hildebrandt@uni-mainz.de)
# - Oliver Kohlbacher (oliver.kohlbacher@uni-tuebingen.de)
# - Hans-Peter Lenhof (lenhof@bioinf.uni-sb.de)
# - others
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301 USA
#
# http://www.ball-project.org
#
# --------------------------------------------------------------------------


option(USE_FFTWD "Use double precision FFTW if found" ON)
option(USE_FFTWF "Use single precision FFTW if found" ON)
option(USE_FFTWF "Use long double precision FFTW if found" ON)
option(USE_FFTW_THREADS "Try to find FFTW with thread support" OFF)

find_package(FFTW)

if(FFTW_FOUND)
	set(BALL_HAS_FFTW TRUE)
	set(BALL_HAS_FFTW_H TRUE)

	# If the libraries are set, set the default traits to the favoured precision (in our case float is prefered
	if(FFTWL_FOUND)
		set(BALL_HAS_FFTW_LONG_DOUBLE TRUE)
		set(FFTW_LIBRARIES ${FFTWL_LIB} ${FFTW_LIBRARIES})
		set(BALL_FFTW_DEFAULT_TRAITS LongDoubleTraits)
		message(STATUS "FFTW: Found long double precision")
	endif()

	if(FFTWD_FOUND)
		set(BALL_HAS_FFTW_DOUBLE TRUE)
		set(FFTW_LIBRARIES ${FFTWD_LIB} ${FFTW_LIBRARIES})
		set(BALL_FFTW_DEFAULT_TRAITS DoubleTraits)
		message(STATUS "FFTW: Found double precision")
	endif()

	if(FFTWF_FOUND)
		set(BALL_HAS_FFTW_FLOAT TRUE)
		set(FFTW_LIBRARIES ${FFTWF_LIB} ${FFTW_LIBRARIES})
		set(BALL_FFTW_DEFAULT_TRAITS FloatTraits)
		message(STATUS "FFTW: Found float precision")
	endif()

	# The user may override these settings
	if(BALL_COMPLEX_PRECISION STREQUAL "float")
		if(FFTWF_FOUND)
			set(BALL_FFTW_DEFAULT_TRAITS FloatTraits)
		else()
			message(SEND_ERROR "An FFTW library needed for ${BALL_COMPLEX_PRECISION} is not available! Thus FFTW-support has been disabled!")
		endif()
	elseif(BALL_COMPLEX_PRECISION STREQUAL "double")
		if(FFTWD_FOUND)
			set(BALL_FFTW_DEFAULT_TRAITS DoubleTraits)
		else()
			message(SEND_ERROR "An FFTW library needed for ${BALL_COMPLEX_PRECISION} is not available! Thus FFTW-support has been disabled!")
		endif()
	elseif(BALL_COMPLEX_PRECISION STREQUAL "long double")
		if(FFTWL_FOUND)
			set(BALL_FFTW_DEFAULT_TRAITS LongDoubleTraits)
		else()
			message(SEND_ERROR "An FFTW library needed for ${BALL_COMPLEX_PRECISION} is not available! Thus FFTW-support has been disabled!")
		endif()
	endif()

	# However we still have to make some settings depending on the selected precision
	IF(BALL_FFTW_DEFAULT_TRAITS STREQUAL "FloatTraits")
		set(BALL_COMPLEX_PRECISION "float")
	elseif (BALL_FFTW_DEFAULT_TRAITS STREQUAL "DoubleTraits")
		set(BALL_COMPLEX_PRECISION "double")
	elseif (BALL_FFTW_DEFAULT_TRAITS STREQUAL "LongDoubleTraits")
		set(BALL_COMPLEX_PRECISION "long double")
	else()
		message(SEND_ERROR "Installed FFTW library features no suitable complex precision (neither float nor double nor long double)")
	endif()

	include_directories(${FFTW_INCLUDE})
	list(APPEND BALL_DEP_LIBRARIES ${FFTW_LIBRARIES})
else()
	set(BALL_HAS_FFTW FALSE)
	set(BALL_HAS_FFTW_H FALSE)
	set(BALL_COMPLEX_PRECISION "float")
	list(APPEND BALL_DEP_MISSING "FFTW")
endif()

