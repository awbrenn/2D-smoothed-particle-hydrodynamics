cmake_minimum_required(VERSION 3.3)
project(sph_particle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
add_compile_options(-std=c++11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

include_directories("/usr/include")
find_library(OIIO "OpenImageIO" "/usr/lib")
find_library(GLUT "glut")
find_library(GL "GL")
find_library(GLU "GLU")

set(SOURCE_FILES main.cpp SPHParticle.cpp SPHParticle.h SPHForce.cpp SPHForce.h SPHSolver.cpp SPHSolver.h vector2.cpp vector2.h SPHOccupancyVolume.cpp SPHOccupancyVolume.h)
add_executable(sph_particle ${SOURCE_FILES})
target_link_libraries(sph_particle ${GLUT} ${GL} ${GLU} ${OIIO})
