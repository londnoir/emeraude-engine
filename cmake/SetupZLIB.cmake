# ZLIB library (Official CMAKE module)

if ( ENABLE_ZLIB )
	find_package(ZLIB REQUIRED)

	message("ZLIB ${ZLIB_VERSION_STRING} library found !")
	message(" - Headers : ${ZLIB_INCLUDE_DIRS}")
	message(" - Binary : ${ZLIB_LIBRARIES}")

	target_include_directories(${PROJECT_NAME} PUBLIC ${ZLIB_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME} PUBLIC ${ZLIB_LIBRARIES})

	set(ZLIB_ENABLED On) # Complete the "libraries_config.hpp" file
endif ()
