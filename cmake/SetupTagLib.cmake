if ( EMERAUDE_USE_SYSTEM_LIBS )

	message("Enabling TagLib library from system ...")

	find_package(PkgConfig REQUIRED)

	pkg_check_modules(TAGLIB REQUIRED taglib)

	target_include_directories(${PROJECT_NAME} PRIVATE ${TAGLIB_INCLUDE_DIRS})
	target_link_directories(${PROJECT_NAME} PRIVATE ${TAGLIB_LIBRARY_DIRS})
	target_link_libraries(${PROJECT_NAME} PRIVATE ${TAGLIB_LIBRARIES})

else ()

	message("Enabling TagLib library from local source ...")

	target_link_libraries(${PROJECT_NAME} PRIVATE tag)

endif ()

set(TAGLIB_ENABLED On) # Complete the "libraries_config.hpp" file
