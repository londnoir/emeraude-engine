# GLM library (Optional) (Alternate math library)

if ( ENABLE_GLM )
	message("Enabling GLM library !")

	if ( USE_SYSTEM_LIBRARIES )
		message("Using system GLM library.")

		find_package(GLM REQUIRED)

		message("GLM ${GLM_VERSION} library found !")
		message(" - Headers : ${GLM_INCLUDE_DIRS}")

		target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_INCLUDE_DIRS})
	else ()
		message("Using embedded GLM library.")

		target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm)
	endif ()

	set(GLM_ENABLED On) # Complete the "libraries_config.hpp" file
endif ()
