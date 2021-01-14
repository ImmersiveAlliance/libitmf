add_library(bmltypes SHARED bmltypes.cxx)
add_library(bmlbitutils SHARED bmlbitutils.cxx)

install(TARGETS bmltypes DESTINATION lib)
install(FILES bmltypes.h DESTINATION include)
install(TARGETS bmlbitutils DESTINATION lib)
install(FILES bmlbitutils.h DESTINATION include)