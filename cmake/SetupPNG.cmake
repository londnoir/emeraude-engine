# LibPNG library (Official CMAKE module)

if ( ENABLE_PNG )
	find_package(PNG REQUIRED)

	message("PNG ${PNG_VERSION_STRING} library found !")
	message(" - Headers : ${PNG_INCLUDE_DIRS}")
	message(" - Binary : ${PNG_LIBRARIES}")

	target_include_directories(${PROJECT_NAME} PUBLIC ${PNG_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME} PUBLIC ${PNG_LIBRARIES})

	set(PNG_ENABLED On) # Complete the "libraries_config.hpp" file
endif ()
