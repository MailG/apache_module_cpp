cmake_minimum_required (VERSION 2.6)

add_custom_command (
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/mod_CXX.conf
	COMMAND sed "s#@@@path@@@#${CMAKE_BINARY_DIR}#" ${CMAKE_SOURCE_DIR}/mod_CXX.conf.in > ${CMAKE_CURRENT_SOURCE_DIR}/mod_CXX.conf
	DEPENDS ${CMAKE_SOURCE_DIR}/mod_CXX.conf.in
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMENT "Generating mod_CXX.conf file")


project(mod_CXX)
set (SRC 
content_manager.cpp
content_manager.h
mod_CXX.cpp
mod_CXX.h
${CMAKE_CURRENT_SOURCE_DIR}/mod_CXX.conf
)
if (UNIX)
set(APACHE_INCLUDE_DIRS /usr/include/apache2 /usr/include/apr-1.0)
else (UNIX)
set(APACHE_INCLUDE_DIRS include/apache2 include/apr-1.0)
endif(UNIX)

include_directories(
	${APACHE_INCLUDE_DIRS}
)

add_library(mod_CXX MODULE ${SRC})

SET_TARGET_PROPERTIES(mod_CXX
         PROPERTIES
         IMPORT_SUFFIX ".so"
         IMPORT_PREFIX ""
         PREFIX ""
) 

if (UNIX)
	set (CONFPATH /etc/apache2/conf.d/)
else(UNIX)
	set (CONFPATH conf.d/)
endif(UNIX)


if (UNIX)
add_custom_target(test
	sudo service apache2 restart && wget -O - 127.0.0.1/CXX
	DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/mod_CXX.conf"
	)

add_custom_target(uninstall
	sudo rm "${CONFPATH}/mod_CXX.conf"
	DEPENDS "${CONFPATH}/mod_CXX.conf"
	)

endif(UNIX)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/mod_CXX.conf" DESTINATION ${CONFPATH})

