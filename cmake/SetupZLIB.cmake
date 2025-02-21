if ( EMERAUDE_USE_SYSTEM_LIBS )

	message("Enabling ZLib library from system ...")

	find_package(PkgConfig REQUIRED)

	pkg_check_modules(ZLIB REQUIRED zlib)

	target_include_directories(${PROJECT_NAME} PUBLIC ${ZLIB_INCLUDE_DIRS})
	target_link_directories(${PROJECT_NAME} PUBLIC ${ZLIB_LIBRARY_DIRS})

else ()

	message("Enabling ZLib library from local source ...")

	if ( NOT EXISTS ${LOCAL_LIB_DIR}/include/zlib.h )
		set(ZLIB_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/zlib)
		set(ZLIB_BUILD_DIR ${TEMPORARY_BUILD_DIR}/zlib-${CMAKE_BUILD_TYPE})

		if ( UNIX AND NOT APPLE )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${ZLIB_SOURCE_DIR}
				-B ${ZLIB_BUILD_DIR}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_C_FLAGS=-fPIC
				-DZLIB_BUILD_EXAMPLES=Off
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		elseif ( APPLE )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${ZLIB_SOURCE_DIR}
				-B ${ZLIB_BUILD_DIR}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_C_FLAGS="-mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET} -fPIC"
				-DZLIB_BUILD_EXAMPLES=Off
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		elseif ( MSVC )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${ZLIB_SOURCE_DIR}
				-B ${ZLIB_BUILD_DIR}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded$<$<CONFIG:Debug>:Debug>
				-DZLIB_BUILD_EXAMPLES=Off
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		else ()
			message(FATAL_ERROR "Unknown platform !")
		endif ()

		execute_process(COMMAND ${CMAKE_COMMAND} --build ${ZLIB_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} --parallel ${CMAKE_BUILD_PARALLEL_LEVEL} COMMAND_ERROR_IS_FATAL ANY)

		execute_process(COMMAND ${CMAKE_COMMAND} --install ${ZLIB_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} COMMAND_ERROR_IS_FATAL ANY)
	endif ()

	set(ZLIB_VERSION "1.3.1git")
	set(ZLIB_INCLUDE_DIRS ${LOCAL_LIB_DIR}/include)
	set(ZLIB_LIBRARY_DIRS ${LOCAL_LIB_DIR}/lib)

	if ( MSVC )
		if ( CMAKE_BUILD_TYPE MATCHES Debug )
			set(ZLIB_LIBRARIES ${LOCAL_LIB_DIR}/lib/zsd.lib)
		else ()
			set(ZLIB_LIBRARIES ${LOCAL_LIB_DIR}/lib/zs.lib)
		endif ()
	else ()
		#set(ZLIB_LIBRARIES z)
		set(ZLIB_LIBRARIES ${LOCAL_LIB_DIR}/lib/libz.a)
	endif ()
endif ()

message("ZLib ${ZLIB_VERSION} library enabled !")
message(" - Headers : ${ZLIB_INCLUDE_DIRS}")
message(" - Libraries : ${ZLIB_LIBRARY_DIRS}")
message(" - Binary : ${ZLIB_LIBRARIES}")

target_link_libraries(${PROJECT_NAME} PUBLIC ${ZLIB_LIBRARIES})

set(ZLIB_ENABLED On) # Complete the "libraries_config.hpp" file
