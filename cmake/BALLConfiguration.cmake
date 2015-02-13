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
# $Authors: $
# -----------------------------------------------------------------------------



INCLUDE(CheckIncludeFileCXX)
INCLUDE(CheckSymbolExists)
INCLUDE(CheckFunctionExists)
INCLUDE(CheckCXXSourceCompiles)
INCLUDE(TestBigEndian)



###############################################################################
###    Important global options and variables used within BALL              ###
###############################################################################


###############################################################################
# Some debug options
#
IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
	SET(BALL_DEBUG TRUE CACHE INTERNAL "BALL configured in debug mode" FORCE)
	SET(BALL_NO_INLINE_FUNCTIONS TRUE CACHE STRING "Reduce usage of inline functions (useful for debugging purposes)")
ELSEIF(CMAKE_BUILD_TYPE STREQUAL "Release")
	SET(BALL_DEBUG FALSE CACHE INTERNAL "BALL configured in debug mode" FORCE)
	SET(BALL_NO_INLINE_FUNCTIONS FALSE CACHE STRING "Reduce usage of inline functions (useful for debugging purposes)")
ENDIF()


###############################################################################
# Defition of some directories
#
IF("${CMAKE_INSTALL_PREFIX}" STREQUAL ".")
	SET(BALL_PATH ${PROJECT_SOURCE_DIR} CACHE STRING "Path to the top level install location.")
	SET(BALL_DATA_PATH ${BALL_PATH}/data CACHE STRING "Path to the BALL data directory.")
ELSE()
	SET(BALL_PATH ${CMAKE_INSTALL_PREFIX} CACHE STRING "Path to the top level install location.")
	SET(BALL_DATA_PATH ${BALL_PATH}/share/BALL/data CACHE STRING "Path to the BALL data directory.")
ENDIF()


###############################################################################
# Information on processor and system type
#
SET(BALL_BINFMT "${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}" CACHE INTERNAL "BALL binary format")
SET(BALL_ARCH ${CMAKE_SYSTEM_PROCESSOR} CACHE INTERNAL "The processor architecture")

# OS
SET(BALL_OS "${CMAKE_SYSTEM_NAME}" CACHE INTERNAL "Operating system")

# OS convenient defines
IF(${BALL_OS} MATCHES "Linux")
	SET(BALL_OS_LINUX TRUE CACHE INTERNAL "This system is a Linux")
ELSEIF(${BALL_OS} MATCHES "SunOS")
	## Try to find out if it's a Solaris or an ancient one...
	IF(${CMAKE_SYSTEM_VERSION} MATCHES "5.*")
		SET(BALL_OS_SOLARIS TRUE CACHE INTERNAL "This system is a Solaris")
	ELSE()
		SET(BALL_OS_SUNOS TRUE CACHE INTERNAL "This system is a SunOS")
	ENDIF()
ELSEIF(${BALL_OS} MATCHES "IRIX")
	SET(BALL_OS_IRIX TRUE CACHE INTERNAL "This system is an IRIX")
ELSEIF(${BALL_OS} MATCHES "FreeBSD")
	SET(BALL_OS_FREEBSD TRUE CACHE INTERNAL "This system is a FreeBSD")
ELSEIF(${BALL_OS} MATCHES "NetBSD")
	SET(BALL_OS_NETBSD TRUE CACHE INTERNAL "This system is a NetBSD")
ELSEIF(${BALL_OS} MATCHES "OpenBSD")
	SET(BALL_OS_OPENBSD TRUE CACHE INTERNAL "This system is an OpenBSD")
ELSEIF(${BALL_OS} MATCHES "Darwin")
	SET(BALL_OS_DARWIN TRUE CACHE INTERNAL "This system is a MacOS X")
ELSEIF(${BALL_OS} MATCHES "Windows")
	SET(BALL_OS_WINDOWS TRUE CACHE INTERNAL "This system is a Windows")
	SET(BALL_PLATFORM_WINDOWS TRUE CACHE INTERNAL "This system is a Windows")
ENDIF()


###############################################################################
# Compiler
#
IF(MSVC)
	SET(BALL_COMPILER_MSVC TRUE CACHE INTERNAL "Do we use the Microsoft Visual Studio Compiler?")
ENDIF()

IF(CMAKE_COMPILER_IS_GNUCXX)
	SET(BALL_COMPILER_GXX TRUE CACHE INTERNAL "Do we use the Gnu Compiler Collection?")
ENDIF()

IF(CMAKE_COMPILER_IS_INTELCXX)
	SET(BALL_COMPILER_INTEL TRUE CACHE INTERNAL "Do we use the Intel Compiler?")
ENDIF()

IF(CMAKE_COMPILER_IS_LLVM)
	SET(BALL_COMPILER_LLVM TRUE CACHE INTERNAL "Do we use the Intel Compiler?")
ENDIF()

SET(BALL_COMPILER "${CXX_COMPILER_ID}" CACHE INTERNAL "The C++ compiler used for BALL" FORCE)
SET(BALL_COMPILER_VERSION "${CXX_COMPILER_VERSION}" CACHE INTERNAL "The C++ compiler version" FORCE)
SET(BALL_COMPILER_VERSION_MAJOR "${CXX_COMPILER_VERSION_MAJOR}" CACHE INTERNAL "The C++ compiler major version" FORCE)
SET(BALL_COMPILER_VERSION_MINOR "${CXX_COMPILER_VERSION_MINOR}" CACHE INTERNAL "The C++ compiler minor version" FORCE)
SET(BALL_COMPILER_VERSION_MINOR_MINOR "${CXX_COMPILER_VERSION_MINOR_MINOR}" CACHE INTERNAL "The C++ compiler minor minor version" FORCE)




###############################################################################
###    System settings                                                      ###
###############################################################################


###############################################################################
# Endianness and type information
#

TEST_BIG_ENDIAN(BALL_BIG_ENDIAN)
IF(BALL_BIG_ENDIAN)
	SET(BALL_LITTLE_ENDIAN FALSE)
ELSE()
	SET(BALL_LITTLE_ENDIAN TRUE)
ENDIF()

INCLUDE(BALLConfigTypes)


###############################################################################
# Check for header files
#

# System headers:
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

# Other headers:
## We *require* regex.h!
CHECK_INCLUDE_FILE_CXX("netinet/in.h" BALL_HAS_NETINET_IN_H)
CHECK_INCLUDE_FILE_CXX("netdb.h" BALL_HAS_NETDB_H)
CHECK_INCLUDE_FILE_CXX("sstream" BALL_HAS_SSTREAM)
CHECK_INCLUDE_FILE_CXX("ieeefp.h" BALL_HAS_IEEEFP_H)
CHECK_INCLUDE_FILE_CXX("values.h" BALL_HAS_VALUES_H)
CHECK_INCLUDE_FILE_CXX("regex.h" BALL_HAS_REGEX_H)
##IF (NOT BALL_HAS_REGEX_H)
##	MESSAGE(SEND_ERROR "Could not find regex.h! Regular expression support is required for BALL!")
##ENDIF()


###############################################################################
# Check functions
#

CHECK_FUNCTION_EXISTS(kill BALL_HAS_KILL)
CHECK_FUNCTION_EXISTS(sysconf BALL_HAS_SYSCONF)
CHECK_FUNCTION_EXISTS(vsnprintf BALL_HAVE_VSNPRINTF)


###############################################################################
# Check symbols
#

MESSAGE(STATUS "Do we need float.h for limits.h?")
CHECK_SYMBOL_EXISTS(FLT_MIN "limits.h" BALL_FLT_MIN_IN_LIMITS_H)
IF(NOT BALL_FLT_MIN_IN_LIMITS_H)
	CHECK_SYMBOL_EXISTS(FLT_MIN "float.h" BALL_HAS_FLOAT_H)

	IF(NOT BALL_HAS_FLOAT_H)
		MESSAGE(SEND_ERROR "limits.h seems to be corrupt or float.h is missing!")
	ENDIF()
ENDIF()


###############################################################################
# Compile checks
#

CHECK_CXX_SOURCE_COMPILES("#include <limits>
	int main(int /*argc*/, char** /*argv*/)
	{
		float f = std::numeric_limits<float>::min();

		return 0;
	}" BALL_HAS_NUMERIC_LIMITS)

CHECK_CXX_SOURCE_COMPILES("#include <sys/stat.h>
	int main(int /*argc*/, char** /*argv*/)
	{
		mode_t x;

		return 0;
	}" BALL_HAS_MODE_T)
IF(NOT BALL_HAS_MODE_T)
	SET(mode_t)
	SET(BALL_MODE_T int)
ENDIF()

# Can we overload long int with LongIndex?
IF(BALL_HAS_STDINT_H)
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

# Do we have an ansi compatible iostream implementation?
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

# Check whether the compiler allows parameterization oftemplate functions
# with inline functions (SGI CC has a problem with that)
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

CHECK_CXX_SOURCE_COMPILES(
	"template<typename T> class A {}; extern template class A<int>; int main() {}"
	BALL_HAS_EXTERN_TEMPLATES
)

CHECK_CXX_SOURCE_COMPILES(
	"template <class T>
	void self_assign(T& t) noexcept(noexcept(t = t))
	{
	    t = t;
	}
	int main(int, char**)
	{
		int x = 1;
		self_assign(x);
		return 0;
	}" BALL_HAS_NOEXCEPT
)


MESSAGE(STATUS "Checking for gnu slist")
CHECK_CXX_SOURCE_COMPILES(
	"#include <ext/slist>
	 int main(int, char**)
	 {
	   __gnu_cxx::slist<int> l;
	   return 0;
	 }" BALL_HAS_GNU_SLIST
)
IF(BALL_HAS_GNU_SLIST)
	MESSAGE(STATUS "Checking for gnu slist - Found")
ELSE()
	MESSAGE(STATUS "Checking for gnu slist - Not found")
ENDIF()

MESSAGE(STATUS "Checking for C++11 initializer lists")
CHECK_CXX_SOURCE_COMPILES(
	"#include <vector>
	 int main(int, char**)
	 {
	   std::vector<int> tmp{1, 2, 3};
	   return 0;
	 }" BALL_HAS_INITIALIZER_LISTS
)
IF(BALL_HAS_INITIALIZER_LISTS)
	MESSAGE(STATUS "Checking for C++11 initializer lists - Found")
ELSE()
	MESSAGE(STATUS "Checking for C++11 initializer lists - Not found")
ENDIF()

CHECK_CXX_SOURCE_COMPILES(
	"int main(int, char**)
	{
		int &&a = 5;
	}" BALL_HAS_RVALUE_REFERENCES
)

CHECK_CXX_SOURCE_COMPILES(
	"#include <string>

	class Bla : std::string
	{
		public:
			Bla(const char* str)
				: std::string(str)
			{
			}
	};

	Bla operator+(std::string&& a, const Bla& blubb)
	{
		return Bla(\"blubb\");
	}

	int main()
	{
		std::string(\"Hiho\") + \"sdfsdf\";
		return 0;
	}" BALL_STD_STRING_HAS_RVALUE_REFERENCES
)

CHECK_CXX_SOURCE_COMPILES(
	"#include <string>
	int main(int, char**)
	{
		std::string s;
		std::string::const_iterator c_it = s.cbegin();

		return 0;
	}" BALL_HAS_STD_STRING_CONST_ITERATORS
)

CHECK_CXX_SOURCE_COMPILES(
	"#include <string>
	int main(int, char**)
	{
		std::string s;
		std::string::const_iterator c_it = s.cbegin();
		s.insert(c_it, 1, 'a');

		return 0;
	}" BALL_HAS_STD_STRING_CONST_ITERATOR_FUNCTIONS
)

CHECK_CXX_SOURCE_COMPILES(
	"#include <string>
	int main(int, char**)
	{
		std::string s;
		s.shrink_to_fit();

		return 0;
	}" BALL_HAS_STD_STRING_SHRINK_TO_FIT
)

CHECK_CXX_SOURCE_COMPILES(
	"#include <string>
	int main(int, char**)
	{
		std::string s;
		s.front();
		s.back();

		return 0;
	}" BALL_HAS_STD_STRING_FRONT_BACK
)

CHECK_CXX_SOURCE_COMPILES(
	"#include <string>
	int main(int, char**)
	{
		std::string s(\"a\");
		s.pop_back();

		return 0;
	}" BALL_HAS_STD_STRING_POP_BACK
)


###############################################################################
# Other stuff - to be checked
#

## Used by GenericPDBFile
SET(BALL_STRICT_PDB_LINE_IMPORT FALSE CACHE BOOL "Use strict checking for PDB line lengths (discouraged!)")
MARK_AS_ADVANCED(BALL_STRICT_PDB_LINE_IMPORT)

SET(BALL_MAX_LINE_LENGTH 65535 CACHE STRING "The maximum line length for reading from files")
MARK_AS_ADVANCED(BALL_MAX_LINE_LENGTH)

## STL-DEBUG (only for GCC and in debug mode)
SET(STL_DEBUG OFF CACHE BOOL "[GCC only] Enable STL-DEBUG mode (very slow).")
IF(STL_DEBUG)
	IF(CMAKE_COMPILER_IS_GNUCXX)
		IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" OR "${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
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


## user flag with default "QMYSQL"
SET(QT_DB_PLUGIN "QMYSQL" CACHE STRING "User switch to change the Qt database plugin.")

## DB test settings
SET(DB_TEST OFF CACHE BOOL "If true, the DB tests are enabled.")
SET(DB_TEST_HOST "localhost" CACHE STRING "Test database server name (only used if DB_TEST is true).")
SET(DB_TEST_PORT "3307" CACHE STRING "Test database server port (only used if DB_TEST is true).")
SET(DB_TEST_DB "OPENMS_TEST_DB" CACHE STRING "Test database name (only used for DB_TEST).")
SET(DB_TEST_USER "openms_test_user" CACHE STRING "Test database user name (only used for DB_TEST).")
SET(DB_TEST_PW "openms_test_password" CACHE STRING "Test database user password (only used for DB_TEST).")
IF(DB_TEST)
	# output
	message(STATUS "DB testing enabled")
	message(STATUS "DB testing - creating credentials files ...")
	# create assorted credentials files
	configure_file(${PROJECT_SOURCE_DIR}/source/TEST/DB_credentials.txt.in ${PROJECT_BINARY_DIR}/source/TEST/DB_credentials.txt)
	configure_file(${PROJECT_SOURCE_DIR}/source/TEST/TOPP/DBImporter.ini.in ${PROJECT_BINARY_DIR}/source/TEST/TOPP/DBImporter.ini)
	configure_file(${PROJECT_SOURCE_DIR}/source/TEST/TOPP/DBExporter.ini.in ${PROJECT_BINARY_DIR}/source/TEST/TOPP/DBExporter.ini)
ENDIF()
