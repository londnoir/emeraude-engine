if ( EMERAUDE_USE_SYSTEM_LIBS )

	message("Enabling FreeType library from system ...")

	find_package(PkgConfig REQUIRED)

	pkg_check_modules(FREETYPE REQUIRED freetype2)

else ()

	message("Enabling FreeType library from local source ...")

	if ( NOT EXISTS ${LOCAL_LIB_DIR}/include/freetype2 )
		set(FREETYPE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/freetype)
		set(FREETYPE_BUILD_DIR ${TEMPORARY_BUILD_DIR}/freetype-${CMAKE_BUILD_TYPE})

		if ( UNIX AND NOT APPLE )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${FREETYPE_SOURCE_DIR}
				-B ${FREETYPE_BUILD_DIR}
				-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_FIND_ROOT_PATH=${LOCAL_LIB_DIR}
				-DCMAKE_C_FLAGS=-fPIC
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		elseif ( APPLE )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${FREETYPE_SOURCE_DIR}
				-B ${FREETYPE_BUILD_DIR}
				-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_FIND_ROOT_PATH=${LOCAL_LIB_DIR}
				-DCMAKE_C_FLAGS="-mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET} -fPIC"
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		elseif ( MSVC )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${FREETYPE_SOURCE_DIR}
				-B ${FREETYPE_BUILD_DIR}
				-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded$<$<CONFIG:Debug>:Debug>
				-DCMAKE_C_FLAGS_RELEASE="/MT" # Requested
				-DCMAKE_C_FLAGS_DEBUG="/MTd" # Requested
				-DCMAKE_FIND_ROOT_PATH=${LOCAL_LIB_DIR}
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		else ()
			message(FATAL_ERROR "Unknown platform !")
		endif ()

		execute_process(COMMAND ${CMAKE_COMMAND} --build ${FREETYPE_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} --parallel ${CMAKE_BUILD_PARALLEL_LEVEL} COMMAND_ERROR_IS_FATAL ANY)

		execute_process(COMMAND ${CMAKE_COMMAND} --install ${FREETYPE_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} COMMAND_ERROR_IS_FATAL ANY)
	endif ()

	set(FREETYPE_VERSION "2.13.3git")
	set(FREETYPE_INCLUDE_DIRS ${LOCAL_LIB_DIR}/include/freetype2)
	set(FREETYPE_LIBRARY_DIRS ${LOCAL_LIB_DIR}/lib)

	if ( MSVC )
		if ( CMAKE_BUILD_TYPE MATCHES Debug )
			set(FREETYPE_LIBRARIES ${LOCAL_LIB_DIR}/lib/freetyped.lib)
		else ()
			set(FREETYPE_LIBRARIES ${LOCAL_LIB_DIR}/lib/freetype.lib)
		endif ()
	else ()
		if ( CMAKE_BUILD_TYPE MATCHES Debug )
			set(FREETYPE_LIBRARIES ${LOCAL_LIB_DIR}/lib/libfreetyped.a)
		else ()
			set(FREETYPE_LIBRARIES ${LOCAL_LIB_DIR}/lib/libfreetype.a)
		endif ()
	endif ()

endif ()

message("FreeType ${FREETYPE_VERSION} library enabled !")
message(" - Headers : ${FREETYPE_INCLUDE_DIRS}")
message(" - Libraries : ${FREETYPE_LIBRARY_DIRS}")
message(" - Binary : ${FREETYPE_LIBRARIES}")

target_include_directories(${PROJECT_NAME} PUBLIC ${FREETYPE_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PUBLIC ${FREETYPE_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${FREETYPE_LIBRARIES})

set(FREETYPE_ENABLED On) # Complete the "libraries_config.hpp" file