if ( EMERAUDE_USE_SYSTEM_LIBS )

	message("Enabling FreeType library from system ...")

	find_package(PkgConfig REQUIRED)

	pkg_check_modules(FREETYPE REQUIRED freetype2)

	target_include_directories(${PROJECT_NAME} PRIVATE ${FREETYPE_INCLUDE_DIRS})
	target_link_directories(${PROJECT_NAME} PRIVATE ${FREETYPE_LIBRARY_DIRS})
	target_link_libraries(${PROJECT_NAME} PRIVATE ${FREETYPE_LIBRARIES})

else ()

	message("Enabling FreeType library from local source ...")

	target_include_directories(${PROJECT_NAME} PUBLIC ${LOCAL_LIB_DIR}/include/freetype2)

	if ( CMAKE_BUILD_TYPE MATCHES Debug )
		target_link_libraries(${PROJECT_NAME} PRIVATE freetyped)
	else ()
		target_link_libraries(${PROJECT_NAME} PRIVATE freetype)
	endif ()

endif ()

set(FREETYPE_ENABLED On) # Complete the "libraries_config.hpp" file
