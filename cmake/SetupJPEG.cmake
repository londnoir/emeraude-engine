if ( EMERAUDE_USE_SYSTEM_LIBS )

	message("Enabling LibJPEG-turbo library from system ...")

	find_package(PkgConfig REQUIRED)

	pkg_check_modules(JPEG REQUIRED libjpeg)

	target_include_directories(${PROJECT_NAME} PUBLIC ${JPEG_INCLUDE_DIRS})
	target_link_directories(${PROJECT_NAME} PUBLIC ${JPEG_LIBRARY_DIRS})

else ()

	message("Enabling LibJPEG-turbo library from local source ...")

	if ( NOT EXISTS ${LOCAL_LIB_DIR}/include/jpeglib.h )
		set(JPEG_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libjpeg-turbo)
		set(JPEG_BUILD_DIR ${TEMPORARY_BUILD_DIR}/libjpeg-turbo-${CMAKE_BUILD_TYPE})

		if ( UNIX AND NOT APPLE )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${JPEG_SOURCE_DIR}
				-B ${JPEG_BUILD_DIR}
				-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_C_FLAGS=-fPIC
				-DENABLE_SHARED=Off
				-DENABLE_STATIC=On
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		elseif ( APPLE )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${JPEG_SOURCE_DIR}
				-B ${JPEG_BUILD_DIR}
				-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_C_FLAGS="-mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET} -fPIC"
				-DENABLE_SHARED=Off
				-DENABLE_STATIC=On
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		elseif ( MSVC )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${JPEG_SOURCE_DIR}
				-B ${JPEG_BUILD_DIR}
				-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded$<$<CONFIG:Debug>:Debug>
				-DENABLE_SHARED=Off
				-DENABLE_STATIC=On
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		else ()
			message(FATAL_ERROR "Unknown platform !")
		endif ()

		execute_process(COMMAND ${CMAKE_COMMAND} --build ${JPEG_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} --parallel ${CMAKE_BUILD_PARALLEL_LEVEL} COMMAND_ERROR_IS_FATAL ANY)

		execute_process(COMMAND ${CMAKE_COMMAND} --install ${JPEG_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} COMMAND_ERROR_IS_FATAL ANY)
	endif()

	set(JPEG_VERSION "3.0.91git")
	set(JPEG_INCLUDE_DIRS ${LOCAL_LIB_DIR}/include)
	set(JPEG_LIBRARY_DIRS ${LOCAL_LIB_DIR}/lib)
	if ( MSVC )
		set(JPEG_LIBRARIES ${LOCAL_LIB_DIR}/lib/jpeg-static.lib)
	else ()
		set(JPEG_LIBRARIES ${LOCAL_LIB_DIR}/lib/libjpeg.a)
	endif ()
endif ()

message("LibJPEG-turbo ${JPEG_VERSION} library enabled !")
message(" - Headers : ${JPEG_INCLUDE_DIRS}")
message(" - Libraries : ${JPEG_LIBRARY_DIRS}")
message(" - Binary : ${JPEG_LIBRARIES}")

target_link_libraries(${PROJECT_NAME} PUBLIC ${JPEG_LIBRARIES})

set(JPEG_ENABLED On) # Complete the "libraries_config.hpp" file
