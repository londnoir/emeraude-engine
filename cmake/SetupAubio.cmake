# Aubio library

if ( ENABLE_AUBIO )
	find_package(Aubio REQUIRED)

	message("Aubio ${AUBIO_VERSION_STRING} library found !")
	message(" - Headers : ${AUBIO_INCLUDE_DIRS}")
	message(" - Binary : ${AUBIO_LIBRARIES}")

	target_include_directories(${PROJECT_NAME} PRIVATE ${AUBIO_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME} PRIVATE ${AUBIO_LIBRARIES})

	set(AUBIO_ENABLED On) # Complete the "emeraude_config.hpp" file
endif ()
