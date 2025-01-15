if ( EMERAUDE_USE_SYSTEM_LIBS )

	message("Enabling LibPNG library from system ...")

	find_package(PkgConfig REQUIRED)

	pkg_check_modules(PNG REQUIRED libpng)

	target_include_directories(${PROJECT_NAME} PUBLIC ${PNG_INCLUDE_DIRS})
	target_link_directories(${PROJECT_NAME} PUBLIC ${PNG_LIBRARY_DIRS})

else ()

	message("Enabling LibPNG library from local source ...")

	if ( NOT EXISTS ${LOCAL_LIB_DIR}/include/png.h )
		set(PNG_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libpng)
		set(PNG_BUILD_DIR ${TEMPORARY_BUILD_DIR}/libpng-${CMAKE_BUILD_TYPE})

		if ( UNIX AND NOT APPLE )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${PNG_SOURCE_DIR}
				-B ${PNG_BUILD_DIR}
				-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_C_FLAGS=-fPIC
				-DZLIB_ROOT=${ZLIB_BINARY_DIR}
				-DPNG_SHARED=Off
				-DPNG_STATIC=On
				-DPNG_TESTS=Off
				-DPNG_TOOLS=Off
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		elseif ( APPLE )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${PNG_SOURCE_DIR}
				-B ${PNG_BUILD_DIR}
				-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_C_FLAGS=-fPIC
				-DZLIB_ROOT=${ZLIB_BINARY_DIR}
				-DPNG_SHARED=Off
				-DPNG_STATIC=On
				-DPNG_TESTS=Off
				-DPNG_TOOLS=Off
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		elseif ( MSVC )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${PNG_SOURCE_DIR}
				-B ${PNG_BUILD_DIR}
				-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded$<$<CONFIG:Debug>:Debug>
				-DCMAKE_C_FLAGS_RELEASE="/MT" # Requested
				-DCMAKE_C_FLAGS_DEBUG="/MTd" # Requested
				-DZLIB_ROOT=${ZLIB_BINARY_DIR}
				-DPNG_SHARED=Off
				-DPNG_STATIC=On
				-DPNG_TESTS=Off
				-DPNG_TOOLS=Off
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		else ()
			message(FATAL_ERROR "Unknown platform !")
		endif ()

		execute_process(COMMAND ${CMAKE_COMMAND} --build ${PNG_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} --parallel ${CMAKE_BUILD_PARALLEL_LEVEL} COMMAND_ERROR_IS_FATAL ANY)

		execute_process(COMMAND ${CMAKE_COMMAND} --install ${PNG_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} COMMAND_ERROR_IS_FATAL ANY)
	endif()

	set(PNG_VERSION "1.6.45git")
	set(PNG_INCLUDE_DIRS ${LOCAL_LIB_DIR}/include)
	set(PNG_LIBRARY_DIRS ${LOCAL_LIB_DIR}/lib)

	if ( MSVC )
		if ( CMAKE_BUILD_TYPE MATCHES Debug )
			set(PNG_LIBRARIES ${LOCAL_LIB_DIR}/lib/libpng16_staticd.lib)
		else ()
			set(PNG_LIBRARIES ${LOCAL_LIB_DIR}/lib/libpng16_static.lib)
		endif ()
	else ()
		if ( CMAKE_BUILD_TYPE MATCHES Debug )
			set(PNG_LIBRARIES ${LOCAL_LIB_DIR}/lib/libpng16d.a)
		else ()
			set(PNG_LIBRARIES ${LOCAL_LIB_DIR}/lib/libpng16.a)
		endif ()
	endif ()

endif ()

message("LibPNG ${PNG_VERSION} library enabled !")
message(" - Headers : ${PNG_INCLUDE_DIRS}")
message(" - Libraries : ${PNG_LIBRARY_DIRS}")
message(" - Binary : ${PNG_LIBRARIES}")

target_link_libraries(${PROJECT_NAME} PUBLIC ${PNG_LIBRARIES})

set(PNG_ENABLED On) # Complete the "libraries_config.hpp" file
