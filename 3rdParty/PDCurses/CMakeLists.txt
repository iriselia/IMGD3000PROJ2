project( PDCURSES )
cmake_minimum_required( VERSION 2.8 )

file(GLOB_RECURSE MY_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src *.cpp *.c)
create_source_group("Source Files" "${CMAKE_CURRENT_SOURCE_DIR}/src" ${MY_SRC})
file(GLOB_RECURSE MY_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
create_source_group("Header Files" "${CMAKE_CURRENT_SOURCE_DIR}/include" ${MY_HEADERS})

set (MY_INCLUDE_DIRS "")
foreach (_headerFile ${MY_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND MY_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES MY_INCLUDE_DIRS)
include_directories( ${MY_INCLUDE_DIRS} )
set(PDCURSES_INCLUDE_DIRS ${MY_INCLUDE_DIRS})

#------ target -----
add_library (PDCurses STATIC ${MY_SRC} ${MY_HEADERS})

if( MSVC )
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
	SET_PROPERTY(TARGET PDCurses		PROPERTY FOLDER "3rd Party")
endif()