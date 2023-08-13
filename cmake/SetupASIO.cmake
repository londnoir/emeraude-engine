# ASIO library (Header only library)

if ( ENABLE_ASIO )
	find_package(ASIO REQUIRED)

	message("ASIO C++ ${ASIO_VERSION} library found !")
	message(" - Headers : ${ASIO_INCLUDE_DIRS}")

	target_include_directories(${PROJECT_NAME} PUBLIC ${ASIO_INCLUDE_DIRS})
	#target_compile_definitions(${PROJECT_NAME} PRIVATE ASIO_STANDALONE ASIO_NO_EXCEPTIONS)

	set(ASIO_ENABLED On) # Complete the "libraries_config.hpp" file
endif ()
