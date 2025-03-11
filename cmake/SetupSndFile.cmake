if ( NOT SNDFILE_ENABLED )
	if ( MSVC )
		message("Enabling SNDFile library from local binary ...")

		set(SNDFILE_VERSION "1.2.2bin")
		set(SNDFILE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libsndfile-1.2.2-win64/include)
		set(SNDFILE_LIBRARY_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libsndfile-1.2.2-win64/lib)
		set(SNDFILE_LIBRARIES sndfile.lib)

		file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
		file(
			COPY_FILE
			${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libsndfile-1.2.2-win64/bin/sndfile.dll
			${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/sndfile.dll
			ONLY_IF_DIFFERENT
		)
	else ()
		message("Enabling SNDFile library from system ...")

		find_package(PkgConfig REQUIRED)

		pkg_check_modules(SNDFILE REQUIRED sndfile)
	endif ()

	message("SndFile ${SNDFILE_VERSION} library enabled !")
	message(" - Headers : ${SNDFILE_INCLUDE_DIRS}")
	message(" - Libraries : ${SNDFILE_LIBRARY_DIRS}")
	message(" - Binary : ${SNDFILE_LIBRARIES}")

	target_include_directories(${PROJECT_NAME} PRIVATE ${SNDFILE_INCLUDE_DIRS})
	target_link_directories(${PROJECT_NAME} PRIVATE ${SNDFILE_LIBRARY_DIRS})
	target_link_libraries(${PROJECT_NAME} PRIVATE ${SNDFILE_LIBRARIES})

	set(SNDFILE_ENABLED On)
else ()
	message("The SNDFile library is already enabled.")
endif ()
