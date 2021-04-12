# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project(itmflib VERSION 1.0)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Uses C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Setting variables
set(itmflib_root "${CMAKE_CURRENT_SOURCE_DIR}")
set(itmflib_src_root "${itmflib_root}/src/itmflib")
set(itmflib_build "${CMAKE_BINARY_DIR}")

# Boost
set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_ADDITIONAL_VERSIONS "1.72" "1.73.0")

cmake_policy(SET CMP0074 NEW)
find_package(Boost REQUIRED)
if(Boost_FOUND)
  message(STATUS ${Boost_INCLUDE_DIR})
  include_directories(${Boost_INCLUDE_DIR})
else()
  message(STATUS "Boost NOT Found ! ${BOOST_ROOT}")
endif(Boost_FOUND)
# enable_testing()

# Subdirectories
# add_subdirectory("${itmflib_src_root}/tests")
add_subdirectory("${itmflib_src_root}/core")
add_subdirectory("${itmflib_src_root}/tools")

