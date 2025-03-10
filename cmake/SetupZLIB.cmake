if ( EMERAUDE_USE_SYSTEM_LIBS )

	message("Enabling ZLib library from system ...")

	find_package(PkgConfig REQUIRED)

	pkg_check_modules(ZLIB REQUIRED zlib)

	target_include_directories(${PROJECT_NAME} PRIVATE ${ZLIB_INCLUDE_DIRS})
	target_link_directories(${PROJECT_NAME} PRIVATE ${ZLIB_LIBRARY_DIRS})
	target_link_libraries(${PROJECT_NAME} PRIVATE ${ZLIB_LIBRARIES})

else ()

	message("Enabling ZLib library from local source ...")

	if ( MSVC )
		if ( CMAKE_BUILD_TYPE MATCHES Debug )
			target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/zsd.lib)
		else ()
			target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/zs.lib)
		endif ()
	else ()
		target_link_libraries(${PROJECT_NAME} PRIVATE z)
	endif ()

endif ()

set(ZLIB_ENABLED On) # Complete the "libraries_config.hpp" file
