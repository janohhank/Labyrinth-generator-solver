# Simple cmakelist file for c++ codes with OpenGL dependency.
# @author Kisházi "janohhank" János

CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

#Project-name
project(Labyrinth)

#Find OpenGL library
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

#Add the source files recursivelly through the subdirectories
file(GLOB_RECURSE SOURCES inc/*.h inc/*.hpp src/*.cpp)

#Add include directories
include_directories(inc)
#Add OpenGL include directories
include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

#Add executable
add_executable(Labyrinth ${SOURCES})

#Link OpenGL libraries
target_link_libraries(Labyrinth ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

#Set compiler flags (c++17 required), GCC or Visual Studio c++
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "-std=c++17 -W -Wall -Wextra -pedantic")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS "-std=c++17")
endif()
