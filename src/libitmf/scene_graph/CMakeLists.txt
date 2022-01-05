# Add source (.cxx and .h) here
set(scenegraph_SRCS
	elements.h
	elements.cxx
	)

include_directories("${itmflib_src_root}/scene_graph")

add_library(itmfscenegraph STATIC ${scenegraph_SRCS})

target_include_directories(itmfscenegraph PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}	
)

message(${CMAKE_CURRENT_SOURCE_DIR})