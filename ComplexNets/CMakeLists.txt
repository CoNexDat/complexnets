set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSTATICLIB")

aux_source_directory(mili SRC_LIST)
aux_source_directory(. SRC_LIST)

file(GLOB HEADERS "**/*.h") 

add_library(ComplexNets ${SRC_LIST} ${HEADERS})
