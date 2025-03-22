if ( NOT SNDFILE_ENABLED )
	if ( MSVC )
		message("Enabling SNDFile library from local binary ...")

		file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

		file(
			COPY_FILE
			${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libsndfile-1.2.2-win64/bin/sndfile.dll
			${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/sndfile.dll
			ONLY_IF_DIFFERENT
		)

		target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libsndfile-1.2.2-win64/include)
		#target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libsndfile-1.2.2-win64/lib)
		target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libsndfile-1.2.2-win64/lib/sndfile.lib)
	else ()
		message("Enabling SNDFile library from system ...")

		find_package(PkgConfig REQUIRED)

		pkg_check_modules(SNDFILE REQUIRED sndfile)

		target_include_directories(${PROJECT_NAME} PRIVATE ${SNDFILE_INCLUDE_DIRS})
		target_link_directories(${PROJECT_NAME} PRIVATE ${SNDFILE_LIBRARY_DIRS})
		target_link_libraries(${PROJECT_NAME} PRIVATE ${SNDFILE_LIBRARIES})
	endif ()

	set(SNDFILE_ENABLED On)
else ()
	message("The SNDFile library is already enabled.")
endif ()
