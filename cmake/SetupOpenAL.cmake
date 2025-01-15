if ( EMERAUDE_USE_SYSTEM_LIBS OR (UNIX AND NOT APPLE) )

	message("Enabling OpenAL library from system ...")

	find_package(OpenAL REQUIRED)

	target_include_directories(${PROJECT_NAME} PUBLIC ${OPENAL_INCLUDE_DIR})
	target_link_directories(${PROJECT_NAME} PUBLIC ${OPENAL_LIBRARY_DIRS})

else ()

	message("Enabling OpenAL-Soft library from local source ...")

	if ( NOT EXISTS ${LOCAL_LIB_DIR}/include/AL )
		set(OPENALSOFT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/openal-soft)
		set(OPENALSOFT_BUILD_DIR ${TEMPORARY_BUILD_DIR}/openal-soft-${CMAKE_BUILD_TYPE})

		if ( UNIX AND NOT APPLE )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${OPENALSOFT_SOURCE_DIR}
				-B ${OPENALSOFT_BUILD_DIR}
				-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_C_FLAGS=-fPIC
				-DCMAKE_CXX_FLAGS=-fPIC
				-DALSOFT_UTILS=Off
				-DALSOFT_NO_CONFIG_UTIL=On
				-DALSOFT_EXAMPLES=Off
				-DALSOFT_TESTS=Off
				-DALSOFT_INSTALL_EXAMPLES=Off
				-DALSOFT_INSTALL_UTILS=Off
				-DC_FLAGS=-fPIC # CHECK
				-DLIBTYPE=STATIC
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		elseif ( APPLE )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${OPENALSOFT_SOURCE_DIR}
				-B ${OPENALSOFT_BUILD_DIR}
				-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_C_FLAGS=-fPIC
				-DCMAKE_CXX_FLAGS=-fPIC
				-DALSOFT_UTILS=Off
				-DALSOFT_NO_CONFIG_UTIL=On
				-DALSOFT_EXAMPLES=Off
				-DALSOFT_TESTS=Off
				-DALSOFT_INSTALL_EXAMPLES=Off
				-DALSOFT_INSTALL_UTILS=Off
				-DLIBTYPE=STATIC
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		elseif ( MSVC )
			execute_process(
				COMMAND ${CMAKE_COMMAND}
				-S ${OPENALSOFT_SOURCE_DIR}
				-B ${OPENALSOFT_BUILD_DIR}
				-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
				-DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
				-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded$<$<CONFIG:Debug>:Debug>
				-DALSOFT_UTILS=Off
				-DALSOFT_NO_CONFIG_UTIL=On
				-DALSOFT_EXAMPLES=Off
				-DALSOFT_TESTS=Off
				-DALSOFT_INSTALL_EXAMPLES=Off
				-DALSOFT_INSTALL_UTILS=Off
				-DLIBTYPE=STATIC
				-DFORCE_STATIC_VCRT=On
				${CMAKE_GEN_EXTRA_FLAGS}
				COMMAND_ERROR_IS_FATAL ANY
			)
		else ()
			message(FATAL_ERROR "Unknown platform !")
		endif ()

		execute_process(COMMAND ${CMAKE_COMMAND} --build ${OPENALSOFT_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} --parallel ${CMAKE_BUILD_PARALLEL_LEVEL} COMMAND_ERROR_IS_FATAL ANY)

		execute_process(COMMAND ${CMAKE_COMMAND} --install ${OPENALSOFT_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} COMMAND_ERROR_IS_FATAL ANY)
	endif()

	set(OPENAL_VERSION_STRING "1.24.1git")
	set(OPENAL_INCLUDE_DIRS ${LOCAL_LIB_DIR}/include)
	set(OPENAL_LIBRARY_DIRS ${LOCAL_LIB_DIR}/lib)
	if ( MSVC )
		set(OPENAL_LIBRARY ${LOCAL_LIB_DIR}/lib/OpenAL32.lib)
	else ()
		set(OPENAL_LIBRARY ${LOCAL_LIB_DIR}/lib/libopenal.a)
	endif ()

	target_compile_definitions(${PROJECT_NAME} PUBLIC AL_LIBTYPE_STATIC)
endif ()

message("OpenAL-Soft ${OPENAL_VERSION_STRING} library enabled !")
message(" - Headers : ${OPENAL_INCLUDE_DIR}")
message(" - Libraries : ${OPENAL_LIBRARY_DIRS}")
message(" - Binary : ${OPENAL_LIBRARY}")

if ( APPLE )
	target_link_libraries(${PROJECT_NAME} PUBLIC "-framework CoreAudio")
	target_link_libraries(${PROJECT_NAME} PUBLIC "-framework AudioToolbox")
elseif ( MSVC )
	target_link_libraries(${PROJECT_NAME} PUBLIC winmm.lib)
	target_link_libraries(${PROJECT_NAME} PUBLIC Avrt.lib)
endif ()

target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENAL_LIBRARY})

set(OPENAL_ENABLED On) # Complete the "emeraude_config.hpp"
