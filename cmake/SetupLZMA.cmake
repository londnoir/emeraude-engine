if ( EMERAUDE_USE_SYSTEM_LIBS )

	message("Enabling LZMA library from system ...")

	find_package(LibLZMA REQUIRED)

	target_include_directories(${PROJECT_NAME} PRIVATE ${LIBLZMA_INCLUDE_DIRS})
	target_link_directories(${PROJECT_NAME} PRIVATE ${LIBLZMA_LIBRARIES})
	target_link_libraries(${PROJECT_NAME} PRIVATE LibLZMA::LibLZMA)

else ()

	message("Enabling LZMA library from local source ...")

	target_link_libraries(${PROJECT_NAME} PRIVATE lzma)
	
endif ()

set(LZMA_ENABLED On) # Complete the "emeraude_config.hpp" file
