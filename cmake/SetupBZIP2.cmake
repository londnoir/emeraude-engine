message("Enabling BZIP2 library from local source ...")

target_link_libraries(${PROJECT_NAME} PRIVATE bz2_static)

set(BZIP2_ENABLED On) # Complete the "libraries_config.hpp" file
