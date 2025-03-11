if ( NOT LZMA_ENABLED )
	if ( EMERAUDE_USE_SYSTEM_LIBS )
		message("Enabling LZMA library from system ...")

		# NOTE: https://cmake.org/cmake/help/latest/module/FindLibLZMA.html
		find_package(LibLZMA REQUIRED)

		target_include_directories(${PROJECT_NAME} PRIVATE ${LIBLZMA_INCLUDE_DIRS})
		target_link_directories(${PROJECT_NAME} PRIVATE ${LIBLZMA_LIBRARIES})
		target_link_libraries(${PROJECT_NAME} PRIVATE LibLZMA::LibLZMA)
	else ()
		message("Enabling LZMA library from local source ...")

		if ( MSVC )
			target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/lzma.lib)
		else ()
			target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/liblzma.a)
		endif ()
	endif ()

	set(LZMA_ENABLED On)
else ()
	message("The LZMA library is already enabled.")
endif ()
