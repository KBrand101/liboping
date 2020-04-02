# CMakeLists.txt

# CMake version required. This must be the very first line, because it sets default policies affecting everything else
cmake_minimum_required(VERSION 3.10.2)

# Force CXX version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project name and version (major.minor.path)
project(liboping VERSION 2.0.0)

# Output dirs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Set build type (defaults to debug)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING
		"Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
		FORCE)
endif()

# Mandatory: Qt5
set(QT_MIN_VERSION "5.9.5")

find_package(Qt5 ${QT_MIN_VERSION} COMPONENTS Core REQUIRED)

# Git revision
if (EXISTS "${CMAKE_SOURCE_DIR}/.git")
	find_package(Git QUIET)
	if(GIT_FOUND)
		execute_process(
			COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
			OUTPUT_VARIABLE GIT_REVISION
		)
		string(REGEX REPLACE "\n" "" GIT_REVISION "${GIT_REVISION}")
		set(LIBOPING_GIT_REVISION "${GIT_REVISION}")
  	else()
		message(STATUS "Git revision could not be determined")
	endif()
endif()

# Get build date
string(TIMESTAMP LIBOPING_BUILD_TIMESTAMP "%Y-%m-%dT%H:%M:%SZ UTC" UTC)

configure_file(config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/src/config.h)

# Finally, go into the subdirs
add_subdirectory(src)