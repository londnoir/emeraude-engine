# GLFW3 library

if ( USE_SYSTEM_LIBRARIES )
	message("Using system GLFW3 library.")

	find_package(PkgConfig REQUIRED)
	pkg_search_module(GLFW REQUIRED glfw3)

	message("GLFW ${GLFW_VERSION} library found !")
	message(" - Headers : ${GLFW_INCLUDE_DIRS}")
	message(" - Binary : ${GLFW_LIBRARIES}")

	target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME} PRIVATE ${GLFW_LIBRARIES}) # ${GLFW_STATIC_LIBRARIES}
else ()
	message("Using embedded GLFW3 library.")

	set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
	set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw glfw EXCLUDE_FROM_ALL)
	target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/include)
	target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
endif ()
