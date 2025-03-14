if ( NOT TAGLIB_ENABLED )
	if ( EMERAUDE_USE_SYSTEM_LIBS )
		message("Enabling TagLib library from system ...")

		find_package(PkgConfig REQUIRED)

		pkg_check_modules(TAGLIB REQUIRED taglib)

		target_include_directories(${PROJECT_NAME} PRIVATE ${TAGLIB_INCLUDE_DIRS})
		target_link_directories(${PROJECT_NAME} PRIVATE ${TAGLIB_LIBRARY_DIRS})
		target_link_libraries(${PROJECT_NAME} PRIVATE ${TAGLIB_LIBRARIES})
	else ()
		message("Enabling TagLib library from local source ...")

		if ( MSVC )
			target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/tag.lib)
		else ()
			target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/libtag.a)
		endif ()
	endif ()

	set(TAGLIB_ENABLED On)
else ()
	message("The TagLib library is already enabled.")
endif ()
