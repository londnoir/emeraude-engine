if ( NOT THREADS_ENABLED )
	message("Enabling Threads library from system ...")

	find_package(Threads REQUIRED)

	if ( Threads_FOUND )
		message("Threads library found !")

		if ( CMAKE_USE_WIN32_THREADS_INIT )
			message("Using win32 thread !")
		endif ()

		if ( CMAKE_USE_PTHREADS_INIT )
			message("Using pthread !")
		endif ()

		if ( CMAKE_HP_PTHREADS_INIT )
			message("Using HP pthread !")
		endif ()

		target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
	endif ()

	set(THREADS_ENABLED On)
else ()
	message("The Threads library is already enabled.")
endif ()
