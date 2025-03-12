message("Enabling Brotli library from local source ...")

if ( MSVC )
	target_link_libraries(${PROJECT_NAME} PRIVATE
		${LOCAL_LIB_DIR}/lib/brotlidec.lib
		${LOCAL_LIB_DIR}/lib/brotlienc.lib
		${LOCAL_LIB_DIR}/lib/brotlicommon.lib
	)
else ()
	target_link_libraries(${PROJECT_NAME} PRIVATE
		${LOCAL_LIB_DIR}/lib/libbrotlidec.a
		${LOCAL_LIB_DIR}/lib/libbrotlienc.a
		${LOCAL_LIB_DIR}/lib/libbrotlicommon.a
	)
endif ()

set(BROTLI_ENABLED On) # Complete the "libraries_config.hpp" file
