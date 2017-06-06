cmake_minimum_required(VERSION 3.8)

project(hw0)

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLUT REQUIRED)

include_directories(include)
link_directories(lib/mac)
add_definitions(-DGL_GLEXT_PROTOTYPES -DOSX)
add_executable(hw0 mytest3.cpp shaders.cpp)
target_link_libraries(hw0 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} m GLEW freeimage)

