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
		target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/jpeg-static.lib)
	else ()
		target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/libjpeg.a)
	endif ()
endif ()

set(JPEG_ENABLED On)
