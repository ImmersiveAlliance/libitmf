# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project(bmllib VERSION 1.0)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Uses C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Setting variables
set(bmllib_root "${CMAKE_CURRENT_SOURCE_DIR}")
set(bmllib_src_root "${bmllib_root}/src/bmllib")
set(bmllib_build "${CMAKE_BINARY_DIR}")

# Boost
set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_ADDITIONAL_VERSIONS "1.72" "1.73")

find_package(Boost REQUIRED)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
else()
  message(STATUS "Boost NOT Found ! ${BOOST_ROOT}")
endif(Boost_FOUND)

# Subdirectories
add_subdirectory("${bmllib_src_root}/core")

# TEMP WHILE LEARNING
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

# Download and unpack googletest at configure time https://github.com/google/googletest/tree/master/googletest
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

include(GoogleTest)

enable_testing()
add_subdirectory("${bmllib_src_root}/tests")