set(bmllib_SRCS
	bmltypes.h
	bmltypes.cxx
	bmlbitutils.h
	bmlbitutils.cxx
	)

set(itmflib_SRCS
	itmfunits.h
	itmfunits.cxx
	itmfenums.h
	itmffile.h
	itmffile.cxx
	)

include_directories("${itmflib_src_root}/core")

add_library(itmfcore STATIC ${itmflib_SRCS} ${bmllib_SRCS} defines.h)

target_include_directories(itmfcore PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}	
)

message(${CMAKE_CURRENT_SOURCE_DIR})