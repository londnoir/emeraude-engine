if ( EMERAUDE_USE_SYSTEM_LIBS )

	message("Enabling HWLOC library from system ...")

	find_package(PkgConfig REQUIRED)

	pkg_check_modules(HWLOC REQUIRED hwloc)

	target_include_directories(${PROJECT_NAME} PUBLIC ${HWLOC_INCLUDE_DIRS})
	target_link_directories(${PROJECT_NAME} PUBLIC ${HWLOC_LIBRARY_DIRS})

else ()

	message("Enabling HWLOC library from local source ...")

	if ( UNIX )

		### Linux/Apple : Using a static library and autoconf

		if ( NOT EXISTS ${LOCAL_LIB_DIR}/include/hwloc )
			set(HWLOC_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/hwloc)

			if ( APPLE )
				message(
					"If that step fails do manually : \n"
					"cd ${CMAKE_CURRENT_SOURCE_DIR}/dependencies \n"
					"bash build-hwloc macOS ${CMAKE_BUILD_TYPE} ${LOCAL_LIB_DIR} \n"
				)

				execute_process(
					COMMAND /bin/bash build-hwloc macOS ${CMAKE_BUILD_TYPE} ${LOCAL_LIB_DIR} ${CMAKE_OSX_DEPLOYMENT_TARGET}
					WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dependencies
					COMMAND_ERROR_IS_FATAL ANY
				)
			else ()
				message(
					"If that step fails do manually : \n"
					"cd ${CMAKE_CURRENT_SOURCE_DIR}/dependencies \n"
					"bash build-hwloc Linux ${CMAKE_BUILD_TYPE} ${LOCAL_LIB_DIR} \n"
				)

				execute_process(
					COMMAND /bin/bash build-hwloc Linux ${CMAKE_BUILD_TYPE} ${LOCAL_LIB_DIR}
					WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dependencies
					COMMAND_ERROR_IS_FATAL ANY
				)
			endif ()
		endif ()

	elseif ( MSVC )

		### Windows : Using dedicated cmake

		if ( NOT EXISTS ${LOCAL_LIB_DIR}/include/hwloc )
			set(HWLOC_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/hwloc/contrib/windows-cmake)
			set(HWLOC_BUILD_DIR ${TEMPORARY_BUILD_DIR}/hwloc-${CMAKE_BUILD_TYPE})

			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${HWLOC_SOURCE_DIR}
				-B ${HWLOC_BUILD_DIR}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded$<$<CONFIG:Debug>:Debug>
				-DHWLOC_ENABLE_TESTING=Off
				-DHWLOC_SKIP_LSTOPO=On
				-DHWLOC_SKIP_TOOLS=On
				-DHWLOC_WITH_LIBXML2=Off
				-DHWLOC_WITH_OPENCL=Off
				-DHWLOC_WITH_CUDA=Off
				-DHWLOC_BUILD_SHARED_LIBS=Off
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)

			execute_process(COMMAND ${CMAKE_COMMAND} --build ${HWLOC_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} --parallel ${CMAKE_BUILD_PARALLEL_LEVEL} COMMAND_ERROR_IS_FATAL ANY)

			execute_process(COMMAND ${CMAKE_COMMAND} --install ${HWLOC_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} COMMAND_ERROR_IS_FATAL ANY)
		endif ()

	else ()

		message(FATAL_ERROR "Unknown platform !")

	endif ()

	set(HARFBUZZ_VERSION "3.0.0git")
	set(HWLOC_INCLUDE_DIRS ${LOCAL_LIB_DIR}/include)
	set(HWLOC_LIBRARY_DIRS ${LOCAL_LIB_DIR}/lib)
	set(HWLOC_LIBRARIES hwloc)

endif ()

message("HWLOC ${HWLOC_VERSION} library enabled !")
message(" - Headers : ${HWLOC_INCLUDE_DIRS}")
message(" - Libraries : ${HWLOC_LIBRARY_DIRS}")
message(" - Binary : ${HWLOC_LIBRARIES}")

target_link_libraries(${PROJECT_NAME} PUBLIC ${HWLOC_LIBRARIES})

if ( APPLE )
	target_link_libraries(${PROJECT_NAME} PUBLIC "-framework IOKit")
endif ()

set(HWLOC_ENABLED On) # Complete the "emeraude_config.hpp" file
