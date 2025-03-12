message("Enabling BZIP2 library from local source ...")

if ( MSVC )
	target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/bz2_static.lib)
else ()
	target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/libbz2_static.a)
endif ()

set(BZIP2_ENABLED On) # Complete the "libraries_config.hpp" file
