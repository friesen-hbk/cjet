IF(NOT CONFIG_NO_HARDENING)
	SET(HARDENING_FLAG "-D_FORTIFY_SOURCE=2")
	
	IF(CMAKE_C_COMPILER_ID STREQUAL GNU)
		IF(CMAKE_C_COMPILER_VERSION VERSION_LESS 4.9.0)
			SET(HARDENING_FLAG "${HARDENING_FLAG} -fstack-protector --param ssp-buffer-size=4" CACHE STRING "" FORCE)
		ELSE()
			SET(HARDENING_FLAG "${HARDENING_FLAG} -fstack-protector-strong" CACHE STRING "" FORCE)
		ENDIF()
	ELSEIF(CMAKE_C_COMPILER_ID STREQUAL Clang)
		IF(CMAKE_C_COMPILER_VERSION VERSION_LESS 3.6.0)
			SET(HARDENING_FLAG "${HARDENING_FLAG} -fstack-protector --param ssp-buffer-size=4" CACHE STRING "" FORCE)
		ELSE()
			SET(HARDENING_FLAG "${HARDENING_FLAG} -fstack-protector-strong" CACHE STRING "" FORCE)
		ENDIF()
	ENDIF()
	
	SET(HARDENING_FLAG "${HARDENING_FLAG} -fpie" CACHE STRING "" FORCE)
	IF(CMAKE_C_COMPILER_ID STREQUAL GNU)
		SET(HARDENING_FLAG "${HARDENING_FLAG} -pie" CACHE STRING "" FORCE)
	ENDIF()
	
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${HARDENING_FLAG}")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${HARDENING_FLAG}")
	
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-z,relro,-z,now")
ENDIF()

