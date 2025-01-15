message("Enabling Brotli library from local source ...")

if ( NOT EXISTS ${LOCAL_LIB_DIR}/include/brotli )
	set(BROTLI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/brotli)
	set(BROTLI_BUILD_DIR ${TEMPORARY_BUILD_DIR}/brotli-${CMAKE_BUILD_TYPE})

	if ( UNIX AND NOT APPLE )
		execute_process(
			COMMAND ${CMAKE_COMMAND}
			-S ${BROTLI_SOURCE_DIR}
			-B ${BROTLI_BUILD_DIR}
			-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
			-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
			-DCMAKE_C_FLAGS=-fPIC
			-DBUILD_SHARED_LIBS=Off
			${CMAKE_GEN_EXTRA_FLAGS}
			COMMAND_ERROR_IS_FATAL ANY
		)
	elseif ( APPLE )
		execute_process(
			COMMAND ${CMAKE_COMMAND}
			-S ${BROTLI_SOURCE_DIR}
			-B ${BROTLI_BUILD_DIR}
			-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
			-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
			-DCMAKE_C_FLAGS="-mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET} -fPIC"
			-DBUILD_SHARED_LIBS=Off
			${CMAKE_GEN_EXTRA_FLAGS}
			COMMAND_ERROR_IS_FATAL ANY
		)
	elseif ( MSVC )
		execute_process(
			COMMAND ${CMAKE_COMMAND}
			-S ${BROTLI_SOURCE_DIR}
			-B ${BROTLI_BUILD_DIR}
			-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
			-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
			-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded$<$<CONFIG:Debug>:Debug>
			-DBUILD_SHARED_LIBS=Off
			${CMAKE_GEN_EXTRA_FLAGS}
			COMMAND_ERROR_IS_FATAL ANY
		)
	else ()
		message(FATAL_ERROR "Unknown platform !")
	endif ()

	execute_process(COMMAND ${CMAKE_COMMAND} --build ${BROTLI_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} --parallel ${CMAKE_BUILD_PARALLEL_LEVEL} COMMAND_ERROR_IS_FATAL ANY)

	execute_process(COMMAND ${CMAKE_COMMAND} --install ${BROTLI_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} COMMAND_ERROR_IS_FATAL ANY)
endif ()

set(BROTLI_VERSION "1.1.0git")
set(BROTLI_INCLUDE_DIRS ${LOCAL_LIB_DIR}/include)
set(BROTLI_LIBRARY_DIRS ${LOCAL_LIB_DIR}/lib)
if ( MSVC )
	set(BROTLI_LIBRARIES
		${LOCAL_LIB_DIR}/lib/brotlidec.lib
		${LOCAL_LIB_DIR}/lib/brotlienc.lib
		${LOCAL_LIB_DIR}/lib/brotlicommon.lib
	)
else ()
	set(BROTLI_LIBRARIES
		${LOCAL_LIB_DIR}/lib/libbrotlidec.a
		${LOCAL_LIB_DIR}/lib/libbrotlienc.a
		${LOCAL_LIB_DIR}/lib/libbrotlicommon.a
	)
endif ()

message("Brotli ${BROTLI_VERSION} library enabled !")
message(" - Headers : ${BROTLI_INCLUDE_DIRS}")
message(" - Libraries : ${BROTLI_LIBRARY_DIRS}")
message(" - Binary : ${BROTLI_LIBRARIES}")

target_link_libraries(${PROJECT_NAME} PUBLIC ${BROTLI_LIBRARIES})

set(BROTLI_ENABLED On) # Complete the "libraries_config.hpp" file
