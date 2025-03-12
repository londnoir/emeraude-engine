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

set(HARFBUZZ_ENABLED On) # Complete the "libraries_config.hpp" file
