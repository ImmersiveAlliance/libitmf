SET(EM_FLAGS "-s WASM=1 -s MODULARIZE=1 -s EXPORT_NAME='ITMF' -s EXTRA_EXPORTED_RUNTIME_METHODS=['FS'] -s EXPORTED_FUNCTIONS=['_free']")

ADD_CUSTOM_COMMAND(
	MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/itmf_web.idl
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/glue_itmf.js ${CMAKE_CURRENT_BINARY_DIR}/glue_itmf.cpp
	COMMAND python $ENV{EMSCRIPTEN}/tools/webidl_binder.py ${CMAKE_CURRENT_SOURCE_DIR}/itmf_web.idl ${CMAKE_CURRENT_BINARY_DIR}/glue_itmf
)
SET_PROPERTY(SOURCE "itmf_webidl_wrapper.cc" APPEND PROPERTY OBJECT_DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/glue_itmf.cpp)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --post-js ${CMAKE_CURRENT_BINARY_DIR}/glue_itmf.js ${EM_FLAGS}")

SET(SRCS
	"itmf_webidl_wrapper.cc"
	"itmf_webidl_wrapper.h"
	"itmf_webidl_glue_wrapper.cc"
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

ADD_EXECUTABLE(itmflib ${SRCS})

target_link_libraries(itmflib itmfcore)

INSTALL(FILES
	${CMAKE_CURRENT_BINARY_DIR}/itmflib.wasm
	DESTINATION dist
	COMPONENT runtime
)