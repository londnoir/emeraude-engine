if ( NOT SAMPLERATE_ENABLED )
	if ( EMERAUDE_USE_SYSTEM_LIBS )
		message("Enabling SampleRate library from system ...")

		find_package(PkgConfig REQUIRED)

		pkg_check_modules(SAMPLERATE REQUIRED samplerate)

		target_include_directories(${PROJECT_NAME} PRIVATE ${SAMPLERATE_INCLUDE_DIRS})
		target_link_directories(${PROJECT_NAME} PRIVATE ${SAMPLERATE_LIBRARY_DIRS})
		target_link_libraries(${PROJECT_NAME} PRIVATE ${SAMPLERATE_LIBRARIES})
	else ()
		message("Enabling SampleRate library from local source ...")

		if ( MSVC )
			target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/samplerate.lib)
		else ()
			target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/libsamplerate.a)
		endif ()
	endif ()

	set(SAMPLERATE_ENABLED On)
else ()
	message("The SampleRate library is already enabled.")
endif ()
