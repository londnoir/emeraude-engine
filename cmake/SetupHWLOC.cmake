if ( NOT HWLOC_ENABLED )
	if ( EMERAUDE_USE_SYSTEM_LIBS )
		message("Enabling HWLOC library from system ...")

		find_package(PkgConfig REQUIRED)

		pkg_check_modules(HWLOC REQUIRED hwloc)

		target_include_directories(${PROJECT_NAME} PRIVATE ${HWLOC_INCLUDE_DIRS})
		target_link_directories(${PROJECT_NAME} PRIVATE ${HWLOC_LIBRARY_DIRS})
		target_link_libraries(${PROJECT_NAME} PRIVATE ${HWLOC_LIBRARIES})
	else ()
		message("Enabling HWLOC library from local source ...")

		if ( MSVC )
			target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/hwloc.lib)
		else ()

			target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/libhwloc.a)

			if ( APPLE )
				target_link_libraries(${PROJECT_NAME} PRIVATE "-framework IOKit")
			endif ()
		endif ()
	endif ()

	set(HWLOC_ENABLED On) # Complete the "emeraude_config.hpp" file
else ()
	message("The HWLOC library is already enabled.")
endif ()
