if ( EMERAUDE_USE_SYSTEM_LIBS )

	message("Enabling LibZib library from system ...")

	find_package(PkgConfig REQUIRED)

	pkg_check_modules(LibZib REQUIRED libzip)

	target_include_directories(${PROJECT_NAME} PRIVATE ${LIBZIP_INCLUDE_DIRS})
	target_link_directories(${PROJECT_NAME} PRIVATE ${LIBZIP_LIBRARY_DIRS})
	target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBZIP_LIBRARIES})

else ()

	message("Enabling LibZib library from local source ...")

	target_link_libraries(${PROJECT_NAME} PRIVATE zip)

endif ()

set(ZIP_ENABLED On) # Complete the "libraries_config.hpp" file
