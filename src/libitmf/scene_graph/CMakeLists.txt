# pugixml
configure_file(CMakeLists.txt.in pugixml-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pugixml-download )
if(result)
  message(FATAL_ERROR "CMake step for pugixml failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pugixml-download )
if(result)
  message(FATAL_ERROR "Build step for pugixml failed: ${result}")
endif()

# Add pugixml directly to our build.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/pugixml-src
                 ${CMAKE_CURRENT_BINARY_DIR}/pugixml-build)

# Add source (.cxx and .h) here
set(scenegraph_SRCS
	attributes.h
	elements.h
	elements.cxx
	enums.h
	)

include_directories("${itmflib_src_root}/scene_graph")

add_library(itmfscenegraph STATIC ${scenegraph_SRCS})

target_include_directories(itmfscenegraph PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}	
)

target_link_libraries(itmfscenegraph pugixml::pugixml)
