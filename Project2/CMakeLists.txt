set( PROJECT_NAME
Project2
)
cmake_minimum_required( VERSION 2.8 )
include( ScanSourceFiles )

#----- Enable Unicode -----
#add_definitions(-DUNICODE -D_UNICODE)

#------ additional includes ------
include_directories(
${CURRENT_INCLUDE_DIRS}
${CMAKE_SOURCE_DIR}/3rdParty/Dragonfly/Include
)

#------ link directories listed ------
link_directories(
${CMAKE_SOURCE_DIR}/lib
)
if(WIN32)
link_libraries(
DragonflyStudentImpl
PDCurses
)
endif(WIN32)

#------ target -----
add_executable (${PROJECT_NAME} ${MY_SRC} ${MY_HEADERS})
