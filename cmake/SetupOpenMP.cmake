message("Enabling OpenMP library from system ...")

if ( MSVC )
	#find_package(OpenMP)

	#target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
	#target_compile_options(${PROJECT_NAME} PUBLIC -openmp:experimental)
else ()
	find_package(OpenMP REQUIRED)

	target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
	target_compile_options(${PROJECT_NAME} PUBLIC -fopenmp)
endif ()
