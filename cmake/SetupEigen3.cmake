if ( NOT EIGEN_ENABLED )
	message("Enabling Eigen3 library (header-only) from local source ...")

	target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/eigen3)

	set(EIGEN_ENABLED On)
else ()
	message("The Eigen3 library is already enabled.")
endif ()
