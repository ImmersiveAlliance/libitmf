add_library(bmltypes bmltypes.cxx)
add_library(bmlbitutils bmlbitutils.cxx)

install(TARGETS bmltypes DESTINATION lib)
install(FILES bmltypes.h DESTINATION include)
install(TARGETS bmlbitutils DESTINATION lib)
install(FILES bmlbitutils.h DESTINATION include)