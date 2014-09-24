cmake_minimum_required( VERSION 2.8 )
# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries

# Include necessary submodules
set(CMAKE_MODULE_PATH
	"${CMAKE_SOURCE_DIR}/CMake"
)

include(SetOutputDirectories)
include(SourceFileScanner)

##----------------------------------------
## End of manual configuration section
## try to minimize tampering with code below unless you know how CMake works
##----------------------------------------
#create solution
parse_project_name(PROJECT_NAME)
project( ${PROJECT_NAME} )

#--- 3rd Party library ---
add_subdirectory( 3rdParty/PDCurses )
add_subdirectory( 3rdParty/Dragonfly )
add_subdirectory( Project2 )