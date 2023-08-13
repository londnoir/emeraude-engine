# SndFile library

if ( ENABLE_SNDFILE )
	find_package(SndFile REQUIRED)

	message("SndFile ${SNDFILE_VERSION} library found !")
	message(" - Headers : ${SNDFILE_INCLUDE_DIRS}")
	message(" - Binary : ${SNDFILE_LIBRARIES}")

	target_include_directories(${PROJECT_NAME} PUBLIC ${SNDFILE_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME} PUBLIC ${SNDFILE_LIBRARIES})

	set(SNDFILE_ENABLED On) # Complete the "libraries_config.hpp" file
endif ()
