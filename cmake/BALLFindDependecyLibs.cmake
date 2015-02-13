# -----------------------------------------------------------------------------
#   BALL - Biochemical ALgorithms Library
#   A C++ framework for molecular modeling and structural bioinformatics.
# -----------------------------------------------------------------------------
#
# Copyright (C) The BALL Team:
#  - Eberhard Karls University, Tuebingen
#  - Saarland University, Saarbrücken
#
# This file is part of BALL.
#
# BALL is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published
# by the Free Software Foundation, either version 3 of the License,
# or (at your option) any later version.
#
# BALL is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with BALL. If not, see <http://www.gnu.org/licenses/>.
#
# -----------------------------------------------------------------------------
# $Maintainer: Philipp Thiel $
# $Authors: Philipp Thiel $
# -----------------------------------------------------------------------------



###############################################################################
###    REQUIRED third party tools and libraries                             ###
###############################################################################


###############################################################################
# EXTERNAL_TOOL: Bison
#
FIND_PACKAGE(BISON)

IF(NOT BISON_FOUND)
	MESSAGE(SEND_ERROR "Could not find Bison parser generator! This is a required dependency for BALL!")
ENDIF()


###############################################################################
# EXTERNAL_TOOL: Flex
#
FIND_PACKAGE(FLEX)

IF(NOT FLEX_FOUND)
	MESSAGE(SEND_ERROR "Could not find Flex scanner generator! This is a required dependency for BALL!")
ENDIF()


###############################################################################
# EXTERNAL_LIB: XDR
#
FIND_PACKAGE(XDR)

IF(XDR_FOUND)
	INCLUDE(BALLConfigXDR)
	LIST(APPEND BALL_DEPENDENCY_LIBS ${XDR_LIBRARIES})
ELSE()
	MESSAGE(FATAL_ERROR "Could not find XDR! This is a required dependency for BALL!")
ENDIF()


###############################################################################
# EXTERNAL_LIB: Qt
#
FIND_PACKAGE(Qt4 4.4.0)

IF(Qt4_FOUND)
	MESSAGE(STATUS "QT qmake at ${QT_QMAKE_EXECUTABLE}")
	MESSAGE(STATUS "QT moc at ${QT_MOC_EXECUTABLE}")
	MESSAGE(STATUS "QT uic at ${QT_UIC_EXECUTABLE}")

	SET(QT_USE_QTCORE TRUE)
	SET(QT_USE_QTGUI TRUE)
	SET(QT_USE_QTNETWORK TRUE)
	SET(QT_USE_QTOPENGL TRUE)
	SET(QT_USE_QTTEST TRUE)
	SET(QT_USE_QTWEBKIT TRUE)
	SET(QT_USE_QTXML TRUE)

	INCLUDE(${QT_USE_FILE})
	LIST(APPEND BALL_DEPENDENCY_LIBS ${QT_LIBRARIES})

	IF(QT_QTWEBKIT_FOUND)
		SET(BALL_HAS_QTWEBKIT TRUE)
		MESSAGE(STATUS "QtWebkit has not been found. Disabling browser support.")
	ENDIF()
ELSE()
	MESSAGE(FATAL_ERROR "Could not find a Qt4 installation! This is a required dependency for BALL!")
ENDIF()


###############################################################################
# EXTERNAL_LIB: BOOST
#
SET(Boost_DETAILED_FAILURE_MSG ON)

SET(BALL_BOOST_COMPONENTS chrono date_time thread iostreams regex serialization system)

FIND_PACKAGE(Boost 1.46 COMPONENTS ${BALL_BOOST_COMPONENTS})

IF(Boost_FOUND)
	MESSAGE(STATUS "Boost include directory: ${Boost_INCLUDE_DIRS}")
	MESSAGE(STATUS "Boost library directory: ${Boost_LIBRARY_DIRS}")

	SET(BOOST_LIBRARIES "")
	SET(BOOST_MISSING_LIBRARIES "")

	FOREACH(COMPONENT ${BALL_BOOST_COMPONENTS})

		STRING(TOUPPER ${COMPONENT} COMPONENT)

		IF(Boost_${COMPONENT}_FOUND)
			SET(BALL_HAS_BOOST_${COMPONENT} TRUE)
			LIST(APPEND BOOST_LIBRARIES ${Boost_${COMPONENT}_LIBRARY})
		ELSE()
			LIST(APPEND BOOST_MISSING_LIBRARIES ${COMPONENT})
		ENDIF()

	ENDFOREACH()

	IF(BOOST_MISSING_LIBRARIES)
		MESSAGE(FATAL_ERROR "The following Boost libraries are missing: ${BOOST_MISSING_LIBRARIES}")
	ELSE()
		# Store the include directories and the libraries
		INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
		LIST(APPEND BALL_DEPENDENCY_LIBS ${BOOST_LIBRARIES})
	ENDIF()
ELSE()
	MESSAGE(FATAL_ERROR "Could not find a suitable Boost installation! This is a required dependency for BALL!")
ENDIF()


###############################################################################
# EXTERNAL_LIB: Eigen3
#
FIND_PACKAGE(Eigen3 3.0.0)

IF(EIGEN3_FOUND)
	INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
ELSE()
	MESSAGE(FATAL_ERROR "Could not find Eigen3! This is a required dependency for BALL!")
ENDIF()


###############################################################################
# EXTERNAL_LIB: OpenBabel2
#
FIND_PACKAGE(OpenBabel2)

IF(OPENBABEL2_FOUND)
	INCLUDE_DIRECTORIES(${OPENBABEL2_INCLUDE_DIRS})
	LIST(APPEND BALL_DEPENDENCY_LIBS ${OPENBABEL2_LIBRARIES})

	SET(BALL_HAS_OPENBABEL TRUE)
ELSE()
	MESSAGE(FATAL_ERROR "Could not find a OpenBabel2 installation! This is a required dependency for BALL!")
ENDIF()


###############################################################################
# EXTERNAL_LIB: GSL
#
FIND_PACKAGE(GSL)

IF(GSL_FOUND)
	ADD_DEFINITIONS(${CMAKE_GSL_CXX_FLAGS})
	INCLUDE_DIRECTORIES(${GSL_INCLUDE_DIR})
	LIST(APPEND BALL_DEPENDENCY_LIBS ${GSL_LIBRARIES})

	SET(BALL_HAS_GSL TRUE)
ELSE()
	MESSAGE(FATAL_ERROR "Could not find GSL! This is a required dependency for BALL!")
ENDIF()



###############################################################################
# EXTERNAL_LIB: LibSVM
#
FIND_PACKAGE(libSVM)

IF(LIBSVM_FOUND)
	MESSAGE(STATUS "LibSVM include directory: ${LIBSVM_INCLUDE_DIR}")
	INCLUDE_DIRECTORIES(${LIBSVM_INCLUDE_DIRS})
	LIST(APPEND BALL_DEPENDENCY_LIBS ${LIBSVM_LIBRARIES})

	SET(BALL_HAS_LIBSVM TRUE)
ELSE()
	MESSAGE(FATAL_ERROR "Could not find LibSVM! This is a required dependency for BALL!")
ENDIF()


###############################################################################
# EXTERNAL_LIB: TBB (Intel)
#
FIND_PACKAGE(TBB)

IF(TBB_FOUND)
	INCLUDE_DIRECTORIES(${TBB_INCLUDE_DIRS})
	BALL_COMBINE_LIBS(TBB_LIBRARIES "${TBB_LIBRARIES}" "${TBB_DEBUG_LIBRARIES}")
	LIST(APPEND BALL_DEPENDENCY_LIBS ${TBB_LIBRARIES})

	SET(BALL_HAS_TBB TRUE)
ELSE()
	MESSAGE(FATAL_ERROR "Could not find Intel TBB! This is a required dependency for BALL!")
ENDIF()


###############################################################################
# EXTERNAL_LIB: LPSolve
#
FIND_PACKAGE(LPSolve)

IF(LPSOLVE_FOUND)
	MESSAGE(STATUS "LPSolve include directory: ${LPSOLVE_INCLUDE_DIR}")
	INCLUDE_DIRECTORIES(${LPSOLVE_INCLUDE_DIR})
	LIST(APPEND BALL_DEPENDENCY_LIBS ${LPSOLVE_LIBRARIES})

	SET(BALL_HAS_LPSOLVE TRUE)
ELSE()
	MESSAGE(FATAL_ERROR "Could not find LPSolve! This is a required dependency for BALL!")
ENDIF()


###############################################################################
# EXTERNAL_LIB: FFTW
#
OPTION(USE_FFTWD "Use double precision FFTW if found" ON)
OPTION(USE_FFTWF "Use single precision FFTW if found" ON)
OPTION(USE_FFTWF "Use long double precision FFTW if found" ON)
OPTION(USE_FFTW_THREADS "Try to find FFTW with thread support" OFF)

FIND_PACKAGE(FFTW)

IF(FFTW_FOUND)
	MESSAGE(STATUS "FFTW include directory: ${FFTW_INCLUDE}")
	INCLUDE(BALLConfigFFTW)
	LIST(APPEND BALL_DEPENDENCY_LIBS ${FFTW_LIBRARIES})
ELSE()
	MESSAGE(FATAL_ERROR "Could not find FFTW! This is a required dependency for BALL!")
ENDIF()

IF(NOT BALL_COMPLEX_PRECISION)
	SET(BALL_COMPLEX_PRECISION "float")
ENDIF()


###############################################################################
# EXTERNAL_LIB: OpenGL
#
FIND_PACKAGE(OpenGL)

IF(OPENGL_FOUND AND OPENGL_GLU_FOUND)
	LIST(APPEND BALL_DEPENDENCY_LIBS ${OPENGL_LIBRARIES})
ELSE()
	MESSAGE(FATAL_ERROR "Could not find gl/glu! This is a required dependency for BALL_view!")
ENDIF()


###############################################################################
# EXTERNAL_LIB: GLEW
#
FIND_PACKAGE(GLEW)

IF(GLEW_FOUND)
	LIST(APPEND BALL_DEPENDENCY_LIBS ${GLEW_LIBRARIES})

	SET(BALL_HAS_GLEW TRUE)
ELSE()
	MESSAGE(FATAL_ERROR "Could not find GLEW! This is a required dependency for BALL_view!")
ENDIF()



###############################################################################
###    OPTIONAL third party tools and libraries                             ###
###############################################################################


###############################################################################
# EXTERNAL_LIB: Cuda
#
OPTION(BALL_REQUIRE_CUDA "CUDA support be required?" OFF)

IF(BALL_REQUIRE_CUDA)
	FIND_PACKAGE(CUDA)
ELSE()
	FIND_PACKAGE(CUDA QUIET)
ENDIF()

IF(FOUND_CUDART)
	#MESSAGE(STATUS "Found CUDA: ${FFTW_INCLUDE}")
	#CUDA_ADD_LIBRARY(BALL ${BALL_sources} ${BALL_headers} ${Cuda_sources})

	SET(BALL_HAS_CUDA TRUE)
ELSE()
	IF(BALL_REQUIRE_CUDA)
		MESSAGE(FATAL_ERROR "Could not find user required CUDA! If not needed skip cmake flag BALL_REQUIRE_MPI")
	ENDIF()
ENDIF()


###############################################################################
# EXTERNAL_LIB: MPI
#
OPTION(BALL_REQUIRE_MPI "MPI support be required?" OFF)

IF(BALL_REQUIRE_MPI)
	FIND_PACKAGE(MPI)
ELSE()
	FIND_PACKAGE(MPI QUIET)
ENDIF()

IF(MPI_FOUND)
	MESSAGE(STATUS "Found MPI: ${MPI_INCLUDE_PATH}")
	ADD_DEFINITIONS(${MPI_COMPILE_FLAGS})
	INCLUDE_DIRECTORIES(${MPI_INCLUDE_PATH})

	SET(BALL_HAS_MPI TRUE)
ELSE()
	IF(BALL_REQUIRE_MPI)
		MESSAGE(FATAL_ERROR "Could not find user required MPI! If not needed skip cmake flag BALL_REQUIRE_MPI")
	ENDIF()
ENDIF()


###############################################################################
# EXTERNAL_LIB: RTFact
#

FIND_PACKAGE(RTFact)

IF(RTFACT_FOUND)
	SET(BALL_HAS_RTFACT TRUE)
	INCLUDE_DIRECTORIES(${RTFACT_INCLUDE_DIR})
	LIST(APPEND BALL_DEPENDENCY_LIBS ${RTFACT_LIBRARIES})

	SET(BALL_HAS_RTFACT TRUE)
ELSE()
	#MESSAGE(FATAL_ERROR "Could not find RTFact! This is a required dependency for BALL!")
	MESSAGE(STATUS "TODO !!! Could not find RTFact! This is a required dependency for BALL!")
ENDIF()
