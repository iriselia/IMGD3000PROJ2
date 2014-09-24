cmake_minimum_required( VERSION 2.8 )

parse_project_name(PROJECT_NAME)
project( ${PROJECT_NAME} )
create_project(CONSOLE)

#----- Enable Unicode -----
#add_definitions(-DUNICODE -D_UNICODE)

#------ additional includes ------
include_directories(
${CMAKE_SOURCE_DIR}/3rdParty/Dragonfly/Include
${CMAKE_SOURCE_DIR}/3rdParty/PDCurses/Include
)

#------ link directories listed ------
link_directories(
${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
)
if(WIN32)
target_link_libraries(
${PROJECT_NAME}
#include libraries below
DragonflyStudentImpl
PDCurses
)
endif(WIN32)

#------ target -----
#add_executable (${PROJECT_NAME} ${arg1} ${MY_SRC} ${MY_HEADERS})
 