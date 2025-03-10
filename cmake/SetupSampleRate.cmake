if ( EMERAUDE_USE_SYSTEM_LIBS )

	message("Enabling SampleRate library from system ...")

	find_package(PkgConfig REQUIRED)

	pkg_check_modules(SAMPLERATE REQUIRED samplerate)

	target_include_directories(${PROJECT_NAME} PRIVATE ${SAMPLERATE_INCLUDE_DIRS})
	target_link_directories(${PROJECT_NAME} PRIVATE ${SAMPLERATE_LIBRARY_DIRS})
	target_link_libraries(${PROJECT_NAME} PRIVATE ${SAMPLERATE_LIBRARIES})

else ()

	message("Enabling SampleRate library from local source ...")

	target_link_libraries(${PROJECT_NAME} PRIVATE samplerate)

endif ()

set(SAMPLERATE_ENABLED On) # Complete the "libraries_config.hpp" file
