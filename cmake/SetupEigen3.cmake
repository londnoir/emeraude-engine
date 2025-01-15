message("Enabling Eigen3 library (header-only) from local source ...")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/eigen3)

set(EIGEN_ENABLED On) # Complete the "libraries_config.hpp" file
