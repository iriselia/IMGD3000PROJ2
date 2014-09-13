project( PROJECT1 )
cmake_minimum_required( VERSION 2.8 )

file(GLOB_RECURSE MY_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src *.cpp *.c)
if( ${MY_SRC})
create_source_group("Source Files" "${CMAKE_CURRENT_SOURCE_DIR}/src" ${MY_SRC})
endif()

file(GLOB_RECURSE MY_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
if( ${MY_HEADERS})
create_source_group("Header Files" "${CMAKE_CURRENT_SOURCE_DIR}/include" ${MY_HEADERS})
endif()

set (MY_INCLUDE_DIRS "")
foreach (_headerFile ${MY_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND MY_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES MY_INCLUDE_DIRS)
include_directories( ${MY_INCLUDE_DIRS} )
set(PROJECT1_INCLUDE_DIRS ${MY_INCLUDE_DIRS})

#------ additional includes ------
include_directories(
${IMGD3000_SOURCE_DIR}/3rdParty/Dragonfly/include
)

#------ link directories listed ------
link_directories(${IMGD3000_SOURCE_DIR}/lib)
if(WIN32)
link_libraries( PDCurses )
link_libraries( ${IMGD3000_SOURCE_DIR}/lib/libdragonfly-cygwin32.a )
link_libraries( ${IMGD3000_SOURCE_DIR}/lib/libdragonfly-cygwin64.a )
endif(WIN32)
#------ target -----
add_executable (Project1 ${MY_SRC} ${MY_HEADERS})