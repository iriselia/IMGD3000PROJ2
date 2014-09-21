## IMGD3000 Project CMake script
##
project( IMGD3000 )
cmake_minimum_required( VERSION 2.8 )

if(WIN32)
add_definitions( "-DPLATFORM_WINDOWS" )
endif(WIN32)

# Include necessary submodules
set(CMAKE_MODULE_PATH
	"${CMAKE_SOURCE_DIR}/CMake"
)

include(FindSourceFiles)
include(SetOutputDirectories)

##----------------------------------------
## End of manual configuration section
## try to minimize tampering with code below unless you know how CMake works
##----------------------------------------


#--- 3rd Party library ---
add_subdirectory( 3rdParty/PDCurses )
add_subdirectory( 3rdParty/Dragonfly )
add_subdirectory( Project2 )