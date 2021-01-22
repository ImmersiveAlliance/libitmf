set(bmllib_SRCS
	bmltypes.h
	bmltypes.cxx
	bmlbitutils.h
	bmlbitutils.cxx)

add_library(bmllib ${bmllib_SRCS})

target_include_directories(bmllib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}	
)
message(${CMAKE_CURRENT_SOURCE_DIR})