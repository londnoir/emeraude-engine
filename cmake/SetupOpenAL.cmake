# OpenAL library (Official CMAKE module)

if ( ENABLE_OPENAL )
	find_package(OpenAL REQUIRED)

	message("OpenAL ${OPENAL_VERSION_STRING} library found !")
	message(" - Headers : ${OPENAL_INCLUDE_DIR}")
	message(" - Binary : ${OPENAL_LIBRARY}")

	target_include_directories(${PROJECT_NAME} PRIVATE ${OPENAL_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENAL_LIBRARY})

	set(OPENAL_ENABLED On) # Complete the "emeraude_config.hpp" file

	# ALUT/FreeALUT library (Optional)

	find_package(ALUT)

	if ( ALUT_FOUND )
		message("FreeALUT ${ALUT_VERSION_STRING} library found !")
		message(" - Headers : ${ALUT_INCLUDE_DIRS}")
		message(" - Binary : ${ALUT_LIBRARIES}")

		target_include_directories(${PROJECT_NAME} PRIVATE ${ALUT_WORKAROUND_INCLUDE_DIRS} ${ALUT_INCLUDE_DIRS})
		target_link_libraries(${PROJECT_NAME} PRIVATE ${ALUT_LIBRARIES})

		set(ALUT_ENABLED On) # Complete the "emeraude_config.hpp" file
	endif ()
endif ()
