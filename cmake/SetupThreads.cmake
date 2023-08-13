# POSIX Thread library (Official CMAKE module)

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

	target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
endif ()
