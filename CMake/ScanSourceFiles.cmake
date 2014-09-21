project( ${PROJECT_NAME} )
cmake_minimum_required( VERSION 2.8 )

file(GLOB_RECURSE MY_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src *.cpp *.c)
if( NOT MY_SRC STREQUAL "" )
create_source_group("Source Files" "${CMAKE_CURRENT_SOURCE_DIR}/src" ${MY_SRC})
endif()

file(GLOB_RECURSE MY_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
if( NOT MY_HEADERS STREQUAL "" )
create_source_group("Header Files" "${CMAKE_CURRENT_SOURCE_DIR}/include" ${MY_HEADERS})
endif()

set (MY_INCLUDE_DIRS "")
foreach (_headerFile ${MY_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND MY_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES MY_INCLUDE_DIRS)

set(${PROJECT_NAME}_INCLUDE_DIRS "${MY_INCLUDE_DIRS}" CACHE STRING "")
include_directories( ${${PROJECT_NAME}_INCLUDE_DIRS} )

#------ target -----
include(GenerateVcxprojUserSettings)
