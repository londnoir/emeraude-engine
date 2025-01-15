if ( EMERAUDE_USE_SYSTEM_LIBS )

	message("Enabling TagLib library from system ...")

	find_package(PkgConfig REQUIRED)

	pkg_check_modules(TAGLIB REQUIRED taglib)

	target_include_directories(${PROJECT_NAME} PUBLIC ${TAGLIB_INCLUDE_DIRS})
	target_link_directories(${PROJECT_NAME} PUBLIC ${TAGLIB_LIBRARY_DIRS})

else ()

	message("Enabling TagLib library from local source ...")

	if ( NOT EXISTS ${LOCAL_LIB_DIR}/include/taglib )
		set(TAGLIB_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/taglib)
		set(TAGLIB_BUILD_DIR ${TEMPORARY_BUILD_DIR}/taglib-${CMAKE_BUILD_TYPE})

		if ( UNIX AND NOT APPLE )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${TAGLIB_SOURCE_DIR}
				-B ${TAGLIB_BUILD_DIR}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_C_FLAGS=-fPIC
				-DCMAKE_CXX_FLAGS=-fPIC
				-DBUILD_SHARED_LIBS=Off
				-DENABLE_STATIC_RUNTIME=On
				-DWITH_ZLIB=Off
				-DBUILD_TESTING=Off
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		elseif ( APPLE )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${TAGLIB_SOURCE_DIR}
				-B ${TAGLIB_BUILD_DIR}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_C_FLAGS="-mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET} -fPIC"
				-DCMAKE_CXX_FLAGS="-mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET} -fPIC"
				-DBUILD_SHARED_LIBS=Off
				-DENABLE_STATIC_RUNTIME=On
				-DWITH_ZLIB=Off
				-DBUILD_TESTING=Off
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		elseif ( MSVC )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${TAGLIB_SOURCE_DIR}
				-B ${TAGLIB_BUILD_DIR}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded$<$<CONFIG:Debug>:Debug>
				-DBUILD_SHARED_LIBS=Off
				-DENABLE_STATIC_RUNTIME=On
				-DWITH_ZLIB=Off
				-DBUILD_TESTING=Off
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		else ()
			message(FATAL_ERROR "Unknown platform !")
		endif ()

		execute_process(COMMAND ${CMAKE_COMMAND} --build ${TAGLIB_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} --parallel ${CMAKE_BUILD_PARALLEL_LEVEL} COMMAND_ERROR_IS_FATAL ANY)

		execute_process(COMMAND ${CMAKE_COMMAND} --install ${TAGLIB_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} COMMAND_ERROR_IS_FATAL ANY)
	endif ()

	set(TAGLIB_VERSION "2.0.2git")
	set(TAGLIB_INCLUDE_DIRS ${LOCAL_LIB_DIR}/include)
	set(TAGLIB_LIBRARY_DIRS ${LOCAL_LIB_DIR}/lib)
	set(TAGLIB_LIBRARIES tag tag_c)

endif ()

message("TagLib ${TAGLIB_VERSION} library enabled !")
message(" - Headers : ${TAGLIB_INCLUDE_DIRS}")
message(" - Libraries : ${TAGLIB_LIBRARY_DIRS}")
message(" - Binary : ${TAGLIB_LIBRARIES}")

target_link_libraries(${PROJECT_NAME} PUBLIC ${TAGLIB_LIBRARIES})

set(TAGLIB_ENABLED On) # Complete the "libraries_config.hpp" file
