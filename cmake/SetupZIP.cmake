if ( NOT LIBZIP_ENABLED )
	if ( EMERAUDE_USE_SYSTEM_LIBS )
		message("Enabling LibZib library from system ...")

		find_package(PkgConfig REQUIRED)

		pkg_check_modules(LIBZIP REQUIRED libzip)

		target_include_directories(${PROJECT_NAME} PRIVATE ${LIBZIP_INCLUDE_DIRS})
		target_link_directories(${PROJECT_NAME} PRIVATE ${LIBZIP_LIBRARY_DIRS})
		target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBZIP_LIBRARIES})
	else ()
		message("Enabling LibZib library from local source ...")

		if ( MSVC )
			target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/zip.lib)
		else ()
			target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/libzip.a)
		endif ()
	endif ()

	set(LIBZIP_ENABLED On)
else ()
	message("The LibZib library is already enabled.")
endif ()
