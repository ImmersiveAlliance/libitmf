# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Uses C++11
project(bmllib VERSION 1.0)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(bmllib_root "${CMAKE_CURRENT_SOURCE_DIR}")
set(bmllib_src_root "${bmllib_root}/src/bmllib")
set(bmllib_build "${CMAKE_BINARY_DIR}")

add_subdirectory("${bmllib_src_root}/core")

add_executable(Main main.cpp)

target_link_libraries(Main PUBLIC
						bmltypes
						bmlbitutils
						)

target_include_directories(Main PUBLIC
						"${bmllib_build}"
						"${bmllib_src_root}/core"
						)

install(TARGETS Main DESTINATION bin)
install(FILES "${bmllib_build}/bmltypes.h"
			  "${bmllib_build}/bmlbitutils.h"
		DESTINATION include)

enable_testing()
include(AddGoogleTest)
add_executable(bmlbitutiltstest "${bmllib_src_root}/core/bmlbitutilstest.cc")