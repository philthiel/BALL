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


# --------------------------------------------------------------------------
# Check architecture
#
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
	message(FATAL_ERROR "Unsupported architecture. Only 64-bits are currently supported by BALL.")
endif()


# --------------------------------------------------------------------------
# Check operating system
#
set(BALL_OS "${CMAKE_SYSTEM_NAME}" CACHE INTERNAL "Operating system")

if(NOT ((${BALL_OS} MATCHES Linux) OR (${BALL_OS} MATCHES Darwin) OR (${BALL_OS} MATCHES Windows)))
	message(FATAL_ERROR "Unsupported operating system. BALL only supports Linux, Mac OSX, and Windows.")
endif()


# --------------------------------------------------------------------------
# Compiler information
#
if(MSVC)
	set(BALL_COMPILER_MSVC TRUE CACHE INTERNAL "Compiler is MSVC")
elseif(CMAKE_COMPILER_IS_GNUCXX)
	set(BALL_COMPILER_GXX TRUE CACHE INTERNAL "Compiler is GNU")
elseif(CMAKE_COMPILER_IS_INTELCXX)
	set(BALL_COMPILER_INTEL TRUE CACHE INTERNAL "Compiler is Intel")
elseif(CMAKE_COMPILER_IS_LLVM)
	SET(BALL_COMPILER_LLVM TRUE CACHE INTERNAL "Compiler is LLVM")
endif()

set(BALL_COMPILER "${CXX_COMPILER_ID}" CACHE INTERNAL "The C++ compiler used for BALL" FORCE)
set(BALL_COMPILER_VERSION "${CXX_COMPILER_VERSION}" CACHE INTERNAL "The C++ compiler version" FORCE)
set(BALL_COMPILER_VERSION_MAJOR "${CXX_COMPILER_VERSION_MAJOR}" CACHE INTERNAL "The C++ compiler major version" FORCE)
set(BALL_COMPILER_VERSION_MINOR "${CXX_COMPILER_VERSION_MINOR}" CACHE INTERNAL "The C++ compiler minor version" FORCE)


# --------------------------------------------------------------------------
# System endianess
#
include(TestBigEndian)

TEST_BIG_ENDIAN(BALL_BIG_ENDIAN)


# --------------------------------------------------------------------------
# Configure system dependent types
#

CHECK_TYPE_SIZE("char"               BALL_CHAR_SIZE)
CHECK_TYPE_SIZE("short"              BALL_SHORT_SIZE)
CHECK_TYPE_SIZE("int"                BALL_INT_SIZE)
CHECK_TYPE_SIZE("long"               BALL_LONG_SIZE)
CHECK_TYPE_SIZE("size_t"             BALL_SIZE_T_SIZE)
CHECK_TYPE_SIZE("void*"              BALL_POINTER_SIZE)
CHECK_TYPE_SIZE("unsigned short"     BALL_USHORT_SIZE)
CHECK_TYPE_SIZE("unsigned int"       BALL_UINT_SIZE)
CHECK_TYPE_SIZE("unsigned long"      BALL_ULONG_SIZE)
CHECK_TYPE_SIZE("unsigned long long" BALL_ULONGLONG_SIZE)
CHECK_TYPE_SIZE("float"              BALL_FLOAT_SIZE)
CHECK_TYPE_SIZE("double"             BALL_DOUBLE_SIZE)

CHECK_TYPE_SIZE("uint64_t" BALL_UINT64_T_SIZE)
if(HAVE_BALL_UINT64_T_SIZE)
	set(BALL_INT64        int64_t)
	set(BALL_UINT64       uint64_t)
	set(BALL_LONG64_TYPE  int64_t)
	set(BALL_ULONG64_TYPE uint64_t)
else()
	message(SEND_ERROR "Could not find appropriate numeric type for 64-bit integers!")
endif()

CHECK_TYPE_SIZE("uint32_t" BALL_UINT32_T_SIZE)
if(HAVE_BALL_UINT32_T_SIZE)
	set(BALL_INT32      int32_t)
	set(BALL_UINT32     uint32_t)
	set(BALL_SIZE_TYPE  uint32_t)
	set(BALL_INDEX_TYPE int32_t)
else()
	message(SEND_ERROR "Could not find appropriate numeric type for 32-bit integers!")
endif()

CHECK_TYPE_SIZE("uint16_t" BALL_UINT16_T_SIZE)
if(HAVE_BALL_UINT16_T_SIZE)
	set(BALL_INT16  int16_t)
	set(BALL_UINT16 uint16_t)
else()
	message(SEND_ERROR "Could not find appropriate numeric type for 16-bit integers!")
endif()

## Define a suitable pointer type
IF (BALL_POINTER_SIZE MATCHES ${BALL_UINT_SIZE})
	SET(BALL_POINTERSIZEUINT_TYPE "unsigned int")
ELSEIF (BALL_POINTER_SIZE MATCHES ${BALL_ULONG_SIZE})
	SET(BALL_POINTERSIZEUINT_TYPE "unsigned long")
ELSEIF (BALL_POINTER_SIZE MATCHES ${BALL_SIZE_T_SIZE})
	SET(BALL_POINTERSIZEUINT_TYPE "size_t")
ELSE()
	MESSAGE(SEND_ERROR "Could not find appropriate integer type of same size as void*")
ENDIF()







# --------------------------------------------------------------------------
# Check out the folowing stuff if needed
#

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CF_BALL_ADDCXX_FLAGS "-std=c++11" ${CF_BALL_ADDCXX_FLAGS})


INCLUDE(CheckIncludeFileCXX)
INCLUDE(CheckSymbolExists)
INCLUDE(CheckFunctionExists)
INCLUDE(CheckCXXSourceCompiles)


## system headers:
CHECK_INCLUDE_FILE_CXX("unistd.h"  BALL_HAS_UNISTD_H)
CHECK_INCLUDE_FILE_CXX("process.h" BALL_HAS_PROCESS_H)
CHECK_INCLUDE_FILE_CXX("time.h"    BALL_HAS_TIME_H)
CHECK_INCLUDE_FILE_CXX("limits.h"  BALL_HAS_LIMITS_H)
CHECK_INCLUDE_FILE_CXX("dirent.h"  BALL_HAS_DIRENT_H)
CHECK_INCLUDE_FILE_CXX("direct.h"  BALL_HAS_DIRECT_H)
CHECK_INCLUDE_FILE_CXX("pwd.h"     BALL_HAS_PWD_H)
CHECK_INCLUDE_FILE_CXX("stdint.h"  BALL_HAS_STDINT_H)

CHECK_INCLUDE_FILE_CXX("sys/ioctl.h"   BALL_HAS_SYS_IOCTL_H)
CHECK_INCLUDE_FILE_CXX("sys/time.h"    BALL_HAS_SYS_TIME_H)
CHECK_INCLUDE_FILE_CXX("sys/stat.h"    BALL_HAS_SYS_STAT_H)
CHECK_INCLUDE_FILE_CXX("sys/times.h"   BALL_HAS_SYS_TIMES_H)
CHECK_INCLUDE_FILE_CXX("sys/types.h"   BALL_HAS_SYS_TYPES_H)
CHECK_INCLUDE_FILE_CXX("sys/param.h"   BALL_HAS_SYS_PARAM_H)
CHECK_INCLUDE_FILE_CXX("sys/socket.h"  BALL_HAS_SYS_SOCKET_H)
CHECK_INCLUDE_FILE_CXX("sys/sysinfo.h" BALL_HAS_SYS_SYSINFO_H)

MESSAGE(STATUS "Do we need float.h for limits.h?")
CHECK_SYMBOL_EXISTS(FLT_MIN "limits.h" BALL_FLT_MIN_IN_LIMITS_H)
IF (NOT BALL_FLT_MIN_IN_LIMITS_H)
	CHECK_SYMBOL_EXISTS(FLT_MIN "float.h" BALL_HAS_FLOAT_H)

	IF (NOT BALL_HAS_FLOAT_H)
		MESSAGE(SEND_ERROR "limits.h seems to be corrupt or float.h is missing!")
	ENDIF()
ENDIF()

## Can we use numeric_limits<>?
CHECK_CXX_SOURCE_COMPILES("#include <limits>
	int main(int /*argc*/, char** /*argv*/)
	{
		float f = std::numeric_limits<float>::min();

		return 0;
	}" BALL_HAS_NUMERIC_LIMITS)

## We *require* regex.h!
CHECK_INCLUDE_FILE_CXX("regex.h" BALL_HAS_REGEX_H)
##IF (NOT BALL_HAS_REGEX_H)
##	MESSAGE(SEND_ERROR "Could not find regex.h! Regular expression support is required for BALL!")
##ENDIF()

CHECK_INCLUDE_FILE_CXX("netinet/in.h" BALL_HAS_NETINET_IN_H)
CHECK_INCLUDE_FILE_CXX("netdb.h" BALL_HAS_NETDB_H)

CHECK_CXX_SOURCE_COMPILES("#include <sys/stat.h>
	int main(int /*argc*/, char** /*argv*/)
	{
		mode_t x;

		return 0;
	}" BALL_HAS_MODE_T)
IF (NOT BALL_HAS_MODE_T)
	SET(mode_t)
	SET(BALL_MODE_T int)
ENDIF()

CHECK_INCLUDE_FILE_CXX("sstream" BALL_HAS_SSTREAM)

CHECK_INCLUDE_FILE_CXX("ieeefp.h" BALL_HAS_IEEEFP_H)
CHECK_INCLUDE_FILE_CXX("values.h" BALL_HAS_VALUES_H)

CHECK_FUNCTION_EXISTS(kill BALL_HAS_KILL)
CHECK_FUNCTION_EXISTS(sysconf BALL_HAS_SYSCONF)

## Can we overload long int with LongIndex?
IF (BALL_HAS_STDINT_H)
	CHECK_CXX_SOURCE_COMPILES("#include <stdint.h>
	void f(long int l) {l+=2;}
	void f(${BALL_LONG64_TYPE} l) {l+=2;}
	int main(int /*argc*/, char** /*argv*/)
	{
		return 0;
	}" BALL_ALLOW_LONG64_TYPE_OVERLOADS)
ELSE()
	CHECK_CXX_SOURCE_COMPILES("
	void f(long int l) {l+=2;}
	void f(${BALL_LONG64_TYPE} l) {l+=2;}
	int main(int /*argc*/, char** /*argv*/)
	{
		return 0;
	}" BALL_ALLOW_LONG64_TYPE_OVERLOADS)
ENDIF()

## Do we have an ansi compatible iostream implementation?
CHECK_CXX_SOURCE_COMPILES("#include <iostream>
	class A : public std::iostream
	{
		A() : std::basic_ios<char>(0),
					std::iostream(0)
		{}
	};

	int main(int /*argc*/, char** /*argv*/)
	{
	}" BALL_HAS_ANSI_IOSTREAM)

## Check whether the compiler allows parameterization oftemplate functions
## with inline functions (SGI CC has a problem with that)
CHECK_CXX_SOURCE_COMPILES("template <int i>
	inline double foo(double x){ return i * x; }

	typedef double (*Function)(double);

	template <Function F>
	inline double bar(double x) { return F(x); }

	int main(int /*argc*/, char** /*argv*/)
	{
		double d = bar< foo<3> >(2.0);

		return 0;
	}" BALL_HAS_INLINE_TPL_ARGS)

## Check for the presence of the slist extension
INCLUDE(BALLConfigSList)

## Check for the presence of C++11 initializer lists
INCLUDE(BALLConfigInitializerList)

## Check for extern templates
INCLUDE(BALLConfigExternTemplates)

## Check for thread_local
INCLUDE(BALLConfigThreadLocal)

## Check for rvalue reference
INCLUDE(BALLConfigRValueReferences)

## Check for the presence of C++11 noexcept
INCLUDE(BALLConfigNoexcept)

## Check for the presence of C++11 features in string
INCLUDE(BALLConfigStdStringFeatures)

## Test whether vsnprintf is available
CHECK_FUNCTION_EXISTS(vsnprintf BALL_HAVE_VSNPRINTF)

## Used by GenericPDBFile
SET(BALL_STRICT_PDB_LINE_IMPORT FALSE CACHE BOOL "Use strict checking for PDB line lengths (discouraged!)")
MARK_AS_ADVANCED(BALL_STRICT_PDB_LINE_IMPORT)

SET(BALL_MAX_LINE_LENGTH 65535 CACHE STRING "The maximum line length for reading from files")
MARK_AS_ADVANCED(BALL_MAX_LINE_LENGTH)

## STL-DEBUG (only for GCC and in debug mode)
SET(STL_DEBUG OFF CACHE BOOL "[GCC only] Enable STL-DEBUG mode (very slow).")
IF (STL_DEBUG)
  IF (CMAKE_COMPILER_IS_GNUCXX)
		IF ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" OR "${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
			# add compiler flag
	ADD_DEFINITIONS(/D_GLIBCXX_DEBUG)
	MESSAGE(STATUS "STL debug mode: ${STL_DEBUG}")
	  ELSE()
	    MESSAGE(WARNING "STL debug mode is supported for BALL debug mode only")
	  ENDIF()
  ELSE()
    MESSAGE(WARNING "STL debug mode is supported for compiler GCC only")
  ENDIF()
ELSE()
	MESSAGE(STATUS "[GCC only] STL debug mode: ${STL_DEBUG}")
ENDIF()
