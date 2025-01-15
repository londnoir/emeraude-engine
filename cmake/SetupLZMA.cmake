if ( EMERAUDE_USE_SYSTEM_LIBS )

	message("Enabling LZMA library from system ...")

	find_package(LibLZMA REQUIRED)

	message("LibLZMA ${LIBLZMA_VERSION} library enabled !")
	message(" - Headers : ${LIBLZMA_INCLUDE_DIRS}")
	message(" - Libraries : ${LIBLZMA_LIBRARIES}")
	message(" - Binary : libzma.a")

	target_include_directories(${PROJECT_NAME} PUBLIC ${LIBLZMA_INCLUDE_DIRS})
	target_link_directories(${PROJECT_NAME} PUBLIC ${LIBLZMA_LIBRARIES})
	target_link_libraries(${PROJECT_NAME} PRIVATE LibLZMA::LibLZMA)

else ()

	message("Enabling LZMA library from local source ...")

	if ( NOT EXISTS ${LOCAL_LIB_DIR}/include/lzma.h )
		set(LIBLZMA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/xz)
		set(LIBLZMA_BUILD_DIR ${TEMPORARY_BUILD_DIR}/xz-${CMAKE_BUILD_TYPE})

		if ( UNIX AND NOT APPLE )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${LIBLZMA_SOURCE_DIR}
				-B ${LIBLZMA_BUILD_DIR}
				-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_C_FLAGS=-fPIC
				-DBUILD_SHARED_LIBS=Off
				-DXZ_SMALL=Off
				-DXZ_EXTERNAL_SHA256=Off
				-DXZ_MICROLZMA_ENCODER=Off
				-DXZ_MICROLZMA_DECODER=Off
				-DXZ_LZIP_DECODER=On
				-DXZ_CLMUL_CRC=On
				-DXZ_ARM64_CRC32=On
				-DXZ_LOONGARCH_CRC32=On
				-DXZ_TOOL_XZDEC=Off
				-DXZ_TOOL_LZMADEC=Off
				-DXZ_TOOL_LZMAINFO=Off
				-DXZ_TOOL_XZ=Off
				-DXZ_TOOL_SCRIPTS=Off
				-DXZ_DOC=Off
				-DXZ_NLS=Off
				-DXZ_TOOL_SYMLINKS=Off
				-DXZ_TOOL_SYMLINKS_LZMA=Off
				-DXZ_DOXYGEN=Off
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		elseif ( APPLE )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${LIBLZMA_SOURCE_DIR}
				-B ${LIBLZMA_BUILD_DIR}
				-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_C_FLAGS="-mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET} -fPIC"
				-DBUILD_SHARED_LIBS=Off
				-DXZ_SMALL=Off
				-DXZ_EXTERNAL_SHA256=Off
				-DXZ_MICROLZMA_ENCODER=Off
				-DXZ_MICROLZMA_DECODER=Off
				-DXZ_LZIP_DECODER=On
				#-DXZ_CLMUL_CRC=On
				-DXZ_ARM64_CRC32=On
				-DXZ_LOONGARCH_CRC32=On
				-DXZ_TOOL_XZDEC=Off
				-DXZ_TOOL_LZMADEC=Off
				-DXZ_TOOL_LZMAINFO=Off
				-DXZ_TOOL_XZ=Off
				-DXZ_TOOL_SCRIPTS=Off
				-DXZ_DOC=Off
				-DXZ_NLS=Off
				#-DXZ_TOOL_SYMLINKS=Off
				-DXZ_TOOL_SYMLINKS_LZMA=Off
				-DXZ_DOXYGEN=Off
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		elseif ( MSVC )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${LIBLZMA_SOURCE_DIR}
				-B ${LIBLZMA_BUILD_DIR}
				#-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} # NOT USED WITH MSVC
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded$<$<CONFIG:Debug>:Debug>
				-DBUILD_SHARED_LIBS=Off
				-DXZ_SMALL=Off
				-DXZ_EXTERNAL_SHA256=Off
				-DXZ_MICROLZMA_ENCODER=Off
				-DXZ_MICROLZMA_DECODER=Off
				-DXZ_LZIP_DECODER=On
				-DXZ_CLMUL_CRC=On
				-DXZ_ARM64_CRC32=On
				-DXZ_LOONGARCH_CRC32=On
				-DXZ_TOOL_XZDEC=Off
				-DXZ_TOOL_LZMADEC=Off
				-DXZ_TOOL_LZMAINFO=Off
				-DXZ_TOOL_XZ=Off
				-DXZ_DOC=Off
				-DXZ_NLS=Off
				-DXZ_THREADS=yes # Check for posix, win95 or vista (yes=autodetect)
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		else ()
			message(FATAL_ERROR "Unknown platform !")
		endif ()

		execute_process(COMMAND ${CMAKE_COMMAND} --build ${LIBLZMA_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} --parallel ${CMAKE_BUILD_PARALLEL_LEVEL} COMMAND_ERROR_IS_FATAL ANY)

		execute_process(COMMAND ${CMAKE_COMMAND} --install ${LIBLZMA_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} COMMAND_ERROR_IS_FATAL ANY)
	endif ()

	set(LIBLZMA_VERSION "5.7.0git")
	set(LIBLZMA_INCLUDE_DIRS ${LOCAL_LIB_DIR}/include)
	set(LIBLZMA_LIBRARY_DIRS ${LOCAL_LIB_DIR}/lib)
	set(LIBLZMA_LIBRARIES lzma)

	message("LZMA ${LIBLZMA_VERSION} library enabled !")
	message(" - Headers : ${LIBLZMA_INCLUDE_DIRS}")
	message(" - Libraries : ${LIBLZMA_LIBRARY_DIRS}")
	message(" - Binary : ${LIBLZMA_LIBRARIES}")

	target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBLZMA_LIBRARIES})
endif ()

set(LZMA_ENABLED On) # Complete the "emeraude_config.hpp" file
