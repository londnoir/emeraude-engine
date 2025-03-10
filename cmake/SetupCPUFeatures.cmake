message("Enabling cpu_features library from local source ...")

target_link_libraries(${PROJECT_NAME} PRIVATE cpu_features)

set(CPUFEATURES_ENABLED On) # Complete the "libraries_config.hpp" file
