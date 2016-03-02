cmake_minimum_required(VERSION 3.3)
project(sph_particle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("/usr/include")
find_library(GLUT "glut")
find_library(GL "GL")
find_library(GLU "GLU")
find_library(X11 "X11")
find_library(M "m")
find_library(XMU "Xmu")

set(SOURCE_FILES main.cpp)
add_executable(sph_particle ${SOURCE_FILES})
target_link_libraries(sph_particle ${M} ${XMU} ${X11} ${GLUT} ${GL} ${GLU})
