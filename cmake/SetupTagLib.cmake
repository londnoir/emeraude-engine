# TagLib library (Optional)

if ( ENABLE_TAGLIB )
	find_package(Taglib REQUIRED)

	message("TagLib ${Taglib_VERSION} library found !")
	message(" - Headers : ${Taglib_INCLUDE_DIRS}")
	message(" - Binary : ${Taglib_LIBRARIES}")

	target_include_directories(${PROJECT_NAME} PRIVATE ${Taglib_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME} PRIVATE ${Taglib_LIBRARIES})

	set(TAGLIB_ENABLED On) # Complete the "emeraude_config.hpp" file
endif ()
