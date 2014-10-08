cmake_minimum_required( VERSION 2.8 )

SET( INCLUDE_DIRS
${Dragonfly_INCLUDE_DIRS}
${PDCurses_INCLUDE_DIRS}
)
SET( LINK_DIRS
)
SET( LINK_LIBS
Dragonfly
PDCurses
)

parse_directory_name(PROJECT_NAME)
project( ${PROJECT_NAME} )
create_project_ex(CONSOLE "${INCLUDE_DIRS}" "${LINK_DIRS}" "${LINK_LIBS}")
