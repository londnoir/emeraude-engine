# Samplerate library

if ( ENABLE_SAMPLERATE )
	find_package(SAMPLERATE REQUIRED)

	message("Samplerate ${SAMPLERATE_VERSION} library found !")
	message(" - Headers : ${SAMPLERATE_INCLUDE_DIRS}")
	message(" - Binary : ${SAMPLERATE_LIBRARIES}")

	target_include_directories(${PROJECT_NAME} PUBLIC ${SAMPLERATE_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME} PUBLIC ${SAMPLERATE_LIBRARIES})

	set(SAMPLERATE_ENABLED On) # Complete the "libraries_config.hpp" file
endif ()