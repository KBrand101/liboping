# src/CMakeLists.txt

# Include directories e.g. libraries
#include_directories(
#	../lib/
#)

# Include source files
add_library(oping STATIC
#	oping.hpp
#	oping.cpp
	liboping.hpp
	liboping.cpp
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_options(oping PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
#			-Werror -Wall -Wextra -Wconversion -Wsign-conversion>
			-Wall -Wextra -Wconversion -Wsign-conversion>
		$<$<CXX_COMPILER_ID:MSVC>:
			/W4>)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	target_compile_options(oping PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
			-Wall -Wextra -Wconversion -Wsign-conversion>
		$<$<CXX_COMPILER_ID:MSVC>:
			/W3>)
endif()