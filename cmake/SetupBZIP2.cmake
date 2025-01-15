message("Enabling BZIP2 library from local source ...")

if ( NOT EXISTS ${LOCAL_LIB_DIR}/include/bzlib.h )
	set(BZIP2_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/bzip2)
	set(BZIP2_BUILD_DIR ${TEMPORARY_BUILD_DIR}/bzip2-${CMAKE_BUILD_TYPE})

	if ( UNIX AND NOT APPLE )
		execute_process(
			COMMAND ${CMAKE_COMMAND}
			-S ${BZIP2_SOURCE_DIR}
			-B ${BZIP2_BUILD_DIR}
			-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
			-DCMAKE_C_FLAGS=-fPIC
			-DENABLE_LIB_ONLY=On
			-DENABLE_SHARED_LIB=Off
			-DENABLE_STATIC_LIB=On
			${CMAKE_GEN_EXTRA_FLAGS}
			COMMAND_ERROR_IS_FATAL ANY
		)
	elseif ( APPLE )
		execute_process(
			COMMAND ${CMAKE_COMMAND}
			-S ${BZIP2_SOURCE_DIR}
			-B ${BZIP2_BUILD_DIR}
			-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
			-DCMAKE_C_FLAGS="-mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET} -fPIC"
			-DENABLE_LIB_ONLY=On
			-DENABLE_SHARED_LIB=Off
			-DENABLE_STATIC_LIB=On
			${CMAKE_GEN_EXTRA_FLAGS}
			COMMAND_ERROR_IS_FATAL ANY
		)
	elseif ( MSVC )
		execute_process(
			COMMAND ${CMAKE_COMMAND}
			-S ${BZIP2_SOURCE_DIR}
			-B ${BZIP2_BUILD_DIR}
			-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
			-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded$<$<CONFIG:Debug>:Debug>
			-DENABLE_LIB_ONLY=On
			-DENABLE_SHARED_LIB=Off
			-DENABLE_STATIC_LIB=On
			${CMAKE_GEN_EXTRA_FLAGS}
			COMMAND_ERROR_IS_FATAL ANY
		)
	else ()
		message(FATAL_ERROR "Unknown platform !")
	endif ()

	execute_process(COMMAND ${CMAKE_COMMAND} --build ${BZIP2_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} --parallel ${CMAKE_BUILD_PARALLEL_LEVEL} COMMAND_ERROR_IS_FATAL ANY)

	execute_process(COMMAND ${CMAKE_COMMAND} --install ${BZIP2_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} COMMAND_ERROR_IS_FATAL ANY)
endif ()

set(BZ2_VERSION "1.1.0git")
set(BZ2_INCLUDE_DIRS ${LOCAL_LIB_DIR}/include)
set(BZ2_LIBRARY_DIRS ${LOCAL_LIB_DIR}/lib)
set(BZ2_LIBRARIES bz2_static)

message("BZIP2 ${BZ2_VERSION} library enabled !")
message(" - Headers : ${LOCAL_LIB_DIR}/include")
message(" - Libraries : ${LOCAL_LIB_DIR}/lib")
message(" - Binary : ${BZ2_LIBRARIES}")

target_link_libraries(${PROJECT_NAME} PUBLIC ${BZ2_LIBRARIES})

set(BZIP2_ENABLED On) # Complete the "libraries_config.hpp" file
