cmake_minimum_required(VERSION 2.8.3)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -msse -msse2 -msse3")

project(clm_bridge)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)
set(ROS_BUILD_TYPE Release)
rosbuild_init()
#rosbuild_genmsg()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )

#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(catkin REQUIRED COMPONENTS message_generation roscpp std_msgs)


find_package( OpenCV 3.0 REQUIRED )
find_package( Boost 1.5.9 REQUIRED COMPONENTS filesystem system)
MESSAGE("Boost information:") 
MESSAGE("  Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}") 
MESSAGE("  Boost_LIBRARIES: ${Boost_LIBRARIES}") 
MESSAGE("  Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}") 

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS}/boost)
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})	

#find_package(TBB REQUIRED)

INCLUDE_DIRECTORIES(${BOOST_INCLUDE_DIR})

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS message_generation roscpp std_msgs
)

include_directories(include ${catkin_INCLUDE_DIRS})
include_directories(include /lib)
link_directories( lib )

# dlib
include_directories(lib/3rdParty/dlib/include)

# Local libraries
#include_directories(${CLM_SOURCE_DIR}/include)

include_directories(lib/local/CLM/include) #resolves includes
include_directories(lib/local/FaceAnalyser/include)	

# dlib library
add_subdirectory(lib/3rdParty/dlib) #compiles these

# CLM library (ordering matters)
add_subdirectory(lib/local/CLM) #compiles these into libraries
add_subdirectory(lib/local/FaceAnalyser)


set (BINNAME1 clm_bridge)

# Set the source files to use with the executable.
set (SRCS1 ${SRCS1} src/clm_bridge.cpp)

# Build the executable that will be used to run this node.
add_executable (${BINNAME1} ${SRCS1})
rosbuild_add_executable (${BINNAME1} ${SRCS1})

target_link_libraries(${BINNAME1} ${catkin_LIBRARIES})
#target_link_libraries(${BINNAME1} libdlib.a)
#target_link_libraries(${BINNAME1} libCLM.a)
#target_link_libraries(${BINNAME1} libFaceAnalyser.a)
#target_link_libraries(${BINNAME1} libCLM.so)
#target_link_libraries(${BINNAME1} libFaceAnalyser.so)
#target_link_libraries(${BINNAME1} ${Boost_LIBRARIES})	

target_link_libraries(${BINNAME1} CLM) #links current build with this library
target_link_libraries(${BINNAME1} FaceAnalyser)
target_link_libraries(${BINNAME1} dlib)
target_link_libraries(${BINNAME1} ${OpenCV_LIBS} ${Boost_LIBRARIES} ${TBB_LIBRARIES})

#add_subdirectory( src )
#add_subdirectory( exe )

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)

install(TARGETS ${BINNAME1}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

catkin_package()


add_custom_command(TARGET ${BINNAME1}
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/build/devel/lib/${BINNAME1}/${BINNAME1} ${PROJECT_BINARY_DIR}/.
)
