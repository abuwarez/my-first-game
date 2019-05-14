cmake_minimum_required (VERSION 3.0)
project (MyFirstGame)

file (GLOB include_dirs
	"."
	".."
)

file (GLOB source_files
	"MyFirstGame.cpp"
	"*/*.h"
	"*/*.cpp"
)

#	"Geometry/*/*.h"	
#	"Geometry/*/*.cpp"	
#	"System/*/*.h"	
#	"System/*/*.cpp"	
#	"Model/*/*.h"	
#	"Model/*/*.cpp"	

SET(GCC_COMPILE_FLAGS "-Wall -Wextra -std=c++11")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

add_executable (MyFirstGame ${source_files})
target_include_directories(MyFirstGame PRIVATE ".")
