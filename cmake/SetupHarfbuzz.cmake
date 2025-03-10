message("Enabling Harfbuzz library from local source ...")

target_link_libraries(${PROJECT_NAME} PRIVATE harfbuzz harfbuzz-subset)

set(HARFBUZZ_ENABLED On) # Complete the "libraries_config.hpp" file
