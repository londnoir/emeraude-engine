if ( NOT BZIP2_ENABLED )
	if ( EMERAUDE_USE_SYSTEM_LIBS )
		message("Enabling bzip2 library from system ...")

		# NOTE: https://cmake.org/cmake/help/latest/module/FindBZip2.html
		find_package(BZip2 REQUIRED)

		target_include_directories(${PROJECT_NAME} PRIVATE ${BZIP2_INCLUDE_DIRS})
		target_link_directories(${PROJECT_NAME} PRIVATE ${BZIP2_LIBRARIES})
		target_link_libraries(${PROJECT_NAME} PRIVATE BZip2::BZip2)
	else ()
		message("Enabling bzip2 library from local source ...")

		if ( MSVC )
			target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/bz2_static.lib)
		else ()
			target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/libbz2_static.a)
		endif ()
	endif ()

	set(BZIP2_ENABLED On)
else ()
	message("The bzip2 library is already enabled.")
endif ()
