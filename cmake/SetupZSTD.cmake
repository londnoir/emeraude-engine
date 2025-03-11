if ( NOT ZSTD_ENABLED )
	if ( EMERAUDE_USE_SYSTEM_LIBS )
		message("Enabling Zstd library from system ...")

		find_package(PkgConfig REQUIRED)

		pkg_check_modules(ZSTD REQUIRED libzstd)

		target_include_directories(${PROJECT_NAME} PRIVATE ${ZSTD_INCLUDE_DIRS})
		target_link_directories(${PROJECT_NAME} PRIVATE ${ZSTD_LIBRARY_DIRS})
		target_link_libraries(${PROJECT_NAME} PRIVATE ${ZSTD_LIBRARIES})
	else ()
		message("Enabling Zstd library from local source ...")

		if ( MSVC )
			#target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/zstd.lib)
		else ()
			target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/libzstd.a)
		endif ()
	endif ()

	set(ZSTD_ENABLED On)
else ()
	message("The Zstd library is already enabled.")
endif ()
