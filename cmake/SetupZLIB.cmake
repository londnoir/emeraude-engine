if ( NOT ZLIB_ENABLED )
	if ( EMERAUDE_USE_SYSTEM_LIBS )
		message("Enabling zlib library from system ...")

		find_package(PkgConfig REQUIRED)

		pkg_check_modules(ZLIB REQUIRED zlib)

		target_include_directories(${PROJECT_NAME} PRIVATE ${ZLIB_INCLUDE_DIRS})
		target_link_directories(${PROJECT_NAME} PRIVATE ${ZLIB_LIBRARY_DIRS})
		target_link_libraries(${PROJECT_NAME} PRIVATE ${ZLIB_LIBRARIES})
	else ()
		message("Enabling zlib library from local source ...")

		if ( MSVC )
			if ( CMAKE_BUILD_TYPE MATCHES Debug )
				target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/zlibstaticd.lib) # Change to 'zsd' when new version of zlib will be released
			else ()
				target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/zlibstatic.lib) # Change to 'zs' when new version of zlib will be released
			endif ()
		else ()
			target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/libz.a) # Change to 'z' when new version of zlib will be released
		endif ()
	endif ()

	set(ZLIB_ENABLED On)
else ()
	message("The zlib library is already enabled.")
endif ()
