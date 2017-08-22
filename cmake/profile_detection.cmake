FUNCTION(LOAD_PROFILE ISA PLATFORM)
	# Obtain sources for the ISA
	FILE(GLOB ISA_SRCS RELATIVE ${CMAKE_SOURCE_DIR} "kern/${ISA}/*.c" "kern/${ISA}/*.cpp" "kern/${ISA}/*.asm" )
	FILE(GLOB PLATFORM_SRCS RELATIVE ${CMAKE_SOURCE_DIR} "kern/${ISA}/${PLATFORM}/*.c" "kern/${ISA}/${PLATFORM}/*.cpp" "kern/${ISA}/${PLATFORM}/*.asm")

	# Load flags associated with ISA and Profile
	INCLUDE("${CMAKE_SOURCE_DIR}/kern/${ISA}/flags.cmake")
	INCLUDE("${CMAKE_SOURCE_DIR}/kern/${ISA}/${PLATFORM}/flags.cmake")

	# Now export our output variables
	SET(PLATFORM_LAYOUT "${CMAKE_SOURCE_DIR}/kern/${ISA}/${PLATFORM}/layout.ld" PARENT_SCOPE)
	SET(ISA_SRCS ${ISA_SRCS} PARENT_SCOPE)
	SET(PLATFORM_SRCS ${PLATFORM_SRCS} PARENT_SCOPE)

	# And specific flags
	SET(ISA_C_FLAGS ${ISA_C_FLAGS} PARENT_SCOPE)
        SET(ISA_CXX_FLAGS ${ISA_CXX_FLAGS} PARENT_SCOPE)
	SET(ISA_ASM_FLAGS ${ISA_ASM_FLAGS} PARENT_SCOPE)
        SET(ISA_LINKER_FLAGS ${ISA_LINKER_FLAGS} PARENT_SCOPE)
	# ...
ENDFUNCTION(LOAD_PROFILE)
