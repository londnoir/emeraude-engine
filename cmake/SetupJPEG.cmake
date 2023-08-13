# LibJPEG library (Official CMAKE module)

if ( ENABLE_JPEG )
	find_package(JPEG REQUIRED)

	message("JPEG ${JPEG_VERSION} library found !")
	message(" - Headers : ${JPEG_INCLUDE_DIRS}")
	message(" - Binary : ${JPEG_LIBRARIES}")

	target_include_directories(${PROJECT_NAME} PUBLIC ${JPEG_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME} PUBLIC ${JPEG_LIBRARIES})

	set(JPEG_ENABLED On) # Complete the "libraries_config.hpp" file
endif ()
