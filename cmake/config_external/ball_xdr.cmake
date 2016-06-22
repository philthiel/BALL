#new_header#


find_package(XDR)

if(XDR_FOUND)
	set(XDR_TEST_HEADER "#include <rpc/types.h>
			#include <rpc/xdr.h>
			extern \"C\" int dummy")
	set(XDR_TEST_FOOTER " {return 0;}
			int main(){
			XDR xdrs;
			xdrrec_create(&xdrs, 0, 0, 0, dummy, dummy);
		}")

	message(STATUS "Checking for xdrrec_create signature")

	set(CMAKE_REQUIRED_LIBRARIES ${XDR_LIBRARIES})

	CHECK_CXX_SOURCE_COMPILES("${XDR_TEST_HEADER}(char*, char*, int)${XDR_TEST_FOOTER}" BALL_XDRREC_CREATE_CHAR_CHAR_INT)

	if(NOT BALL_XDRREC_CREATE_CHAR_CHAR_INT)
		CHECK_CXX_SOURCE_COMPILES("${XDR_TEST_HEADER}(void*, char*, int)${XDR_TEST_FOOTER}" BALL_XDRREC_CREATE_VOID_CHAR_INT)
		if(NOT BALL_XDRREC_CREATE_VOID_CHAR_INT)
			CHECK_CXX_SOURCE_COMPILES("${XDR_TEST_HEADER}(void*, void*, unsigned int)${XDR_TEST_FOOTER}" BALL_XDRREC_CREATE_VOID_VOID_UINT)
			if(NOT BALL_XDRREC_CREATE_VOID_VOID_UINT)
				CHECK_CXX_SOURCE_COMPILES("${XDR_TEST_HEADER}()${XDR_TEST_FOOTER}" BALL_XDRREC_CREATE_VOID)
				if(NOT BALL_XDRREC_CREATE_VOID)
					CHECK_CXX_SOURCE_COMPILES("${XDR_TEST_HEADER}(void*, void*, int)${XDR_TEST_FOOTER}" BALL_XDRREC_CREATE_VOID_VOID_INT)
					if(NOT BALL_XDRREC_CREATE_VOID_VOID_INT)
						set(BALL_HAS_XDR TRUE)
						message(SEND_ERROR "Could not determine xdrrec_create signature")
					endif()
				endif()
			endif()
		endif()
	endif()

	set(CMAKE_REQUIRED_LIBRARIES)

	set(BALL_HAS_XDR TRUE)
	list(APPEND TMP_DEP_LIBS ${XDR_LIBRARIES})
else()
	set(BALL_HAS_XDR FALSE)
	list(APPEND TMP_DEP_MISSING "xdr")
endif()
