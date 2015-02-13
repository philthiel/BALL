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
# $Maintainer: $
# $Authors: Andreas Moll, Philipp Thiel, others $
# -----------------------------------------------------------------------------


PROJECT("BALLView")


###############################################################################
###    Upstream include directories                                         ###
###############################################################################

# BALLView include directory for configured files
INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})

# BALL_core include directories
INCLUDE_DIRECTORIES(${BALL_core_INCLUDE_DIRS})

# BALL_view include directories
INCLUDE_DIRECTORIES(${BALL_view_INCLUDE_DIRS})


###############################################################################
###    Set BALLView sources                                                 ###
###############################################################################

# List all filenames of the directory here ###
SET(SOURCES_LIST
	demoTutorialDialog.C
	icons.C
	main.C
	mainframe.C
)

# List of all files requiring a moc run ###
SET(MOC_SOURCES_LIST
	demoTutorialDialog.h
	mainframe.h
)

SET(UI_SOURCES_LIST
	aboutDialog.ui
	demoTutorialDialog.ui
)

SET(RCC_SOURCES_LIST
	splashscreen.qrc
)

SET(RESOURCES_LIST
	BALLView.rc
)

IF(BALL_OS_DARWIN)
	LIST(APPEND RESOURCES_LIST "${PROJECT_SOURCE_DIR}/cmake/installer/BALLView.icns")
	SET(MACOSX_BUNDLE_ICON_FILE BALLView.icns)
	SET_SOURCE_FILES_PROPERTIES("${PROJECT_SOURCE_DIR}/cmake/installer/BALLView.icns" PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
ENDIF()

QT4_WRAP_CPP(MOC_OUTFILES ${MOC_SOURCES_LIST})
QT4_ADD_RESOURCES(RCC_OUTFILES ${RCC_SOURCES_LIST})
QT4_WRAP_UI(UIC_OUTFILES ${UI_SOURCES_LIST})


###############################################################################
###    Add BALLView target                                                  ###
###############################################################################

ADD_EXECUTABLE(BALLView
	${SOURCES_LIST}
	${MOC_OUTFILES}
	${RCC_OUTFILES}
	${UIC_OUTFILES}
	${RESOURCES_LIST}
)

TARGET_LINK_LIBRARIES(BALLView BALL_core BALL_view ${BALL_DEPENDENCY_LIBS})










