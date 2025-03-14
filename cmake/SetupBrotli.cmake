if ( NOT BROTLI_ENABLED )
	if ( EMERAUDE_USE_SYSTEM_LIBS )
		# NOTE: Brotli is unnecessary from system, freetype as system library will do the job.
	else ()
		message("Enabling bzip2 library from local source ...")

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
	endif ()

	set(BROTLI_ENABLED On)
else ()
	message("The Brotli library is already enabled.")
endif ()
