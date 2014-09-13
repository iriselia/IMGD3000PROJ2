## IMGD3000 Project CMake script
##
project( IMGD3000 )
cmake_minimum_required( VERSION 2.8 )

if(WIN32)
add_definitions( "-DPLATFORM_WINDOWS" )
endif(WIN32)

# Include necessary submodules
set(CMAKE_MODULE_PATH
	"${IMGD3000_SOURCE_DIR}/CMake"
)

include(FindSourceFiles)

##----------------------------------------
## End of manual configuration section
## try to minimize tampering with code below unless you know how CMake works
##----------------------------------------

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${IMGD3000_SOURCE_DIR}/bin CACHE PATH "Single Directory for all executables." )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${IMGD3000_SOURCE_DIR}/bin CACHE PATH "Single Directory for all executables." )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${IMGD3000_SOURCE_DIR}/bin_debug CACHE PATH "Single Directory for all executables." )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${IMGD3000_SOURCE_DIR}/lib CACHE PATH "Single Directory for all static libraries." )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${IMGD3000_SOURCE_DIR}/lib CACHE PATH "Single Directory for all static libraries." )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${IMGD3000_SOURCE_DIR}/lib CACHE PATH "Single Directory for all static libraries." )
SET( CMAKE_PDB_OUTPUT_DIRECTORY ${IMGD3000_SOURCE_DIR}/bin_debug/pdb CACHE PATH "Single Directory for all static libraries." )
SET( CMAKE_INCLUDE_CURRENT_DIR ON )

#--- 3rd Party library ---
add_subdirectory( 3rdParty/PDCurses )
add_subdirectory( 3rdParty/Dragonfly )
add_subdirectory( Project1 )