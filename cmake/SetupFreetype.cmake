# FreeType library (Official CMAKE module)

if ( ENABLE_FREETYPE )
	find_package(Freetype REQUIRED)

	message("Freetype ${FREETYPE_VERSION_STRING} library found !")
	message(" - Headers : ${FREETYPE_INCLUDE_DIRS}")
	message(" - Binary : ${FREETYPE_LIBRARIES}")

	target_include_directories(${PROJECT_NAME} PUBLIC ${FREETYPE_INCLUDE_DIRS}) # ft2build.h include bug when PRIVATE
	target_link_libraries(${PROJECT_NAME} PUBLIC ${FREETYPE_LIBRARIES})

	set(FREETYPE_ENABLED On) # Complete the "libraries_config.hpp" file
endif ()
