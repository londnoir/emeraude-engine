if ( NOT FREETYPE_ENABLED )
	if ( EMERAUDE_USE_SYSTEM_LIBS )
		message("Enabling FreeType library from system ...")

		# NOTE: https://cmake.org/cmake/help/latest/module/FindFreetype.html
		find_package(Freetype REQUIRED)

		target_include_directories(${PROJECT_NAME} PUBLIC ${FREETYPE_INCLUDE_DIRS})
		target_link_libraries(${PROJECT_NAME} PRIVATE Freetype::Freetype)
	else ()

		message("Enabling FreeType library from local source ...")

		target_include_directories(${PROJECT_NAME} PUBLIC ${LOCAL_LIB_DIR}/include/freetype2)

		if ( MSVC )
			if ( CMAKE_BUILD_TYPE MATCHES Debug )
				target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/freetyped.lib)
			else ()
				target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/freetype.lib)
			endif ()
		else ()
			if ( CMAKE_BUILD_TYPE MATCHES Debug )
				target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/libfreetyped.a)
			else ()
				target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/libfreetype.a)
			endif ()
		endif ()
	endif ()

	set(FREETYPE_ENABLED On)
else ()
	message("The FreeType library is already enabled.")
endif ()
