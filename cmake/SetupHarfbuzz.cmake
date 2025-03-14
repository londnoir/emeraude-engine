if ( NOT HARFBUZZ_ENABLED )
	if ( EMERAUDE_USE_SYSTEM_LIBS )
		# NOTE: Harfbuzz is unnecessary from system, freetype as system library will do the job.
	else ()
		message("Enabling Harfbuzz library from local source ...")

		if ( MSVC )
			target_link_libraries(${PROJECT_NAME} PRIVATE
				${LOCAL_LIB_DIR}/lib/harfbuzz.lib
				${LOCAL_LIB_DIR}/lib/harfbuzz-subset.lib
			)
		else ()
			target_link_libraries(${PROJECT_NAME} PRIVATE
				${LOCAL_LIB_DIR}/lib/libharfbuzz.a
				${LOCAL_LIB_DIR}/lib/libharfbuzz-subset.a
			)
		endif ()
	endif ()

	set(HARFBUZZ_ENABLED On)
else ()
	message("The Harfbuzz library is already enabled.")
endif ()
