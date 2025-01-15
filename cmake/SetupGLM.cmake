message("Enabling GLM library (header-only) from local source ...")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm)

set(GLM_ENABLED On) # Complete the "libraries_config.hpp" file
