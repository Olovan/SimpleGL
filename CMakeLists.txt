cmake_minimum_required(VERSION 2.6)
project (SimpleGL) #Set Project name

set (CMAKE_CXX_STANDARD 11) #Force C++11 standards for access to std libraries
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
cmake_policy(SET CMP0015 NEW) #Enforce new cmake policy to convert relative paths to absolute paths

#Set Defines
add_definitions( -DGLFW-STATIC -DGLEW_STATIC -static )      

#add include to include directories
include_directories(include)

#add lib directories
link_directories(./dependencies/glfw/lib
		 ./dependencies/glew/lib
		)

#Set Libs
set(LINK_LIBS 
	      glfw3
	      glew32
	      opengl32
	      )



#add src files
file(GLOB SOURCES "src/*.cpp")
set(SOURCES ${SOURCES} main.cpp)
#set(SOURCES ${SOURCES} src/GLEW/glew.c)


add_executable(main ${SOURCES})
target_link_libraries(main ${LINK_LIBS})
