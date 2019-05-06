cmake_minimum_required (VERSION 3.0)
project (MyFirstGame)

file (GLOB include_files
	"Geometry/*.h"
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

add_executable (MyFirstGame ${source_files})
target_include_directories(MyFirstGame PRIVATE ${include_files})
