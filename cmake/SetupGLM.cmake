if ( NOT GLM_ENABLED )
	message("Enabling GLM library (header-only) from local source ...")

	target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm)

	set(GLM_ENABLED On)
else ()
	message("The GLM library is already enabled.")
endif ()
