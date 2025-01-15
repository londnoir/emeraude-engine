message("Configuring GLSLang library as sub-project ...")

find_package(Python3 REQUIRED COMPONENTS Interpreter)

message("Launching '${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glslang/update_glslang_sources.py' ...")

execute_process(COMMAND ${Python3_EXECUTABLE} update_glslang_sources.py WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glslang/ COMMAND_ERROR_IS_FATAL ANY)

set(GLSLANG_TESTS_DEFAULT Off CACHE BOOL "" FORCE)
set(GLSLANG_ENABLE_INSTALL_DEFAULT Off CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS Off CACHE BOOL "" FORCE)
set(ENABLE_GLSLANG_BINARIES Off CACHE BOOL "" FORCE)
set(ENABLE_GLSLANG_JS Off CACHE BOOL "" FORCE)

set(ENABLE_HLSL Off CACHE BOOL "" FORCE)
set(ENABLE_RTTI On CACHE BOOL "" FORCE)
set(ENABLE_EXCEPTIONS Off CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glslang glslang EXCLUDE_FROM_ALL)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glslang/glslang/Include)
target_link_libraries(${PROJECT_NAME} PUBLIC glslang SPIRV)
