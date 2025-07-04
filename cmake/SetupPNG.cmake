if ( NOT PNG_ENABLED )
	# FIXME: PNG and GTK 3 fails together
	if ( EMERAUDE_USE_SYSTEM_LIBS OR (UNIX AND NOT APPLE) )
		message("Enabling LibPNG library from system ...")

		find_package(PkgConfig REQUIRED)

		pkg_check_modules(PNG REQUIRED libpng)

		target_include_directories(${PROJECT_NAME} PRIVATE ${PNG_INCLUDE_DIRS})
		target_link_directories(${PROJECT_NAME} PRIVATE ${PNG_LIBRARY_DIRS})
		target_link_libraries(${PROJECT_NAME} PRIVATE ${PNG_LIBRARIES})
	else ()
		message("Enabling LibPNG library from local source ...")

		if ( MSVC )
			if ( CMAKE_BUILD_TYPE MATCHES Debug )
				target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/libpng16_staticd.lib)
			else ()
				target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/libpng16_static.lib)
			endif ()
		else ()
			if ( CMAKE_BUILD_TYPE MATCHES Debug )
				target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/libpng16d.a)
			else ()
				target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/libpng16.a)
			endif ()
		endif ()
	endif ()

	set(PNG_ENABLED On)
else ()
	message("The ASIO LibPNG is already enabled.")
endif ()
