# Eigen 3 library (Optional) (Alternate math library)

if ( EM_ENABLE_EIGEN )
	message("Enabling Eigen 3 library !")

	if ( EM_USE_SYSTEM_LIBRARIES )
		message("Using system Eigen 3 library.")

		find_package(Eigen3 REQUIRED)

		message("Eigen ${EIGEN3_VERSION} library found !")
		message("Including ${EIGEN3_INCLUDE_DIR} ... ")

		target_include_directories(${PROJECT_NAME} PUBLIC ${EIGEN3_INCLUDE_DIR})
	else ()
		message("Using embedded Eigen 3 library.")

		target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/eigen3)
	endif ()

	set(EIGEN_ENABLED On) # Complete the "libraries_config.hpp" file
endif ()
