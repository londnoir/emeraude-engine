message("Configuring GLFW3 framework as sub-project ...")

set(BUILD_SHARED_LIBS Off CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES Off CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS Off CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS Off CACHE BOOL "" FORCE)
set(GLFW_INSTALL Off CACHE BOOL "" FORCE)
set(GLFW_USE_HYBRID_HPG On)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw EXCLUDE_FROM_ALL)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/include)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
