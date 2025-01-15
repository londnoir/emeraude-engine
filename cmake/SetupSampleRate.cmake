if ( EMERAUDE_USE_SYSTEM_LIBS )

	message("Enabling SampleRate library from system ...")

	find_package(PkgConfig REQUIRED)

	pkg_check_modules(SAMPLERATE REQUIRED samplerate)

	target_include_directories(${PROJECT_NAME} PUBLIC ${SAMPLERATE_INCLUDE_DIRS})
	target_link_directories(${PROJECT_NAME} PUBLIC ${SAMPLERATE_LIBRARY_DIRS})

else ()

	message("Enabling SampleRate library from local source ...")

	if ( NOT EXISTS ${LOCAL_LIB_DIR}/include/samplerate.h )
		set(SAMPLERATE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libsamplerate)
		set(SAMPLERATE_BUILD_DIR ${TEMPORARY_BUILD_DIR}/libsamplerate-${CMAKE_BUILD_TYPE})

		if ( UNIX AND NOT APPLE )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${SAMPLERATE_SOURCE_DIR}
				-B ${SAMPLERATE_BUILD_DIR}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_C_FLAGS=-fPIC
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		elseif ( APPLE )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${SAMPLERATE_SOURCE_DIR}
				-B ${SAMPLERATE_BUILD_DIR}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_C_FLAGS="-mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET} -fPIC"
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		elseif ( MSVC )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${SAMPLERATE_SOURCE_DIR}
				-B ${SAMPLERATE_BUILD_DIR}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded$<$<CONFIG:Debug>:Debug>
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		else ()
			message(FATAL_ERROR "Unknown platform !")
		endif ()

		execute_process(COMMAND ${CMAKE_COMMAND} --build ${SAMPLERATE_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} --parallel ${CMAKE_BUILD_PARALLEL_LEVEL} COMMAND_ERROR_IS_FATAL ANY)

		execute_process(COMMAND ${CMAKE_COMMAND} --install ${SAMPLERATE_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} COMMAND_ERROR_IS_FATAL ANY)
	endif ()

	set(SAMPLERATE_VERSION "0.2.2git")
	set(SAMPLERATE_INCLUDE_DIRS ${LOCAL_LIB_DIR}/include)
	set(SAMPLERATE_LIBRARY_DIRS ${LOCAL_LIB_DIR}/lib)
	set(SAMPLERATE_LIBRARIES samplerate)

endif ()

message("SampleRate ${SAMPLERATE_VERSION} library enabled !")
message(" - Headers : ${SAMPLERATE_INCLUDE_DIRS}")
message(" - Libraries : ${SAMPLERATE_LIBRARY_DIRS}")
message(" - Binary : ${SAMPLERATE_LIBRARIES}")

target_link_libraries(${PROJECT_NAME} PUBLIC samplerate)

set(SAMPLERATE_ENABLED On) # Complete the "libraries_config.hpp" file
