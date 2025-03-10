if ( EMERAUDE_USE_SYSTEM_LIBS )

	message("Enabling LibJPEG-turbo library from system ...")

	find_package(PkgConfig REQUIRED)

	pkg_check_modules(JPEG REQUIRED libjpeg)

	target_include_directories(${PROJECT_NAME} PRIVATE ${JPEG_INCLUDE_DIRS})
	target_link_directories(${PROJECT_NAME} PRIVATE ${JPEG_LIBRARY_DIRS})
	target_link_libraries(${PROJECT_NAME} PRIVATE ${JPEG_LIBRARIES})

else ()

	message("Enabling LibJPEG-turbo library from local source ...")

	if ( MSVC )
		target_link_libraries(${PROJECT_NAME} PRIVATE jpeg-static)
	else ()
		target_link_libraries(${PROJECT_NAME} PRIVATE jpeg)
	endif ()
endif ()

set(JPEG_ENABLED On) # Complete the "libraries_config.hpp" file
