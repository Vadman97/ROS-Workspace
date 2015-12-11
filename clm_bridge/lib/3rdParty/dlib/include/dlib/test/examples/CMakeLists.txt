set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -msse -msse2 -msse3")
# Disable some warnings from gcc when compiling the examples because fixing them would make the
# examples harder to read.
if (CMAKE_COMPILER_IS_GNUCXX)
   add_definitions("-Wno-comment -Wno-unused-parameter")
endif()

add_subdirectory(../../../examples examples_build)
