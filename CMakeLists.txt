cmake_minimum_required( VERSION 2.8 )
project(read_obj)

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

 
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OpenGL_INCLUDE_DIR})
include_directories(${GLUT_INCLUDE_DIRS})

add_definitions(${GLUT_DEFINITIONS})
add_definitions(${OpenGL_DEFINITIONS})

link_directories(${OpenGL_LIBRARY_DIR})



add_executable( test1 test1.cpp )
target_link_libraries( test1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
