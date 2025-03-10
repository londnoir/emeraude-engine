message("Enabling Brotli library from local source ...")

target_link_libraries(${PROJECT_NAME} PRIVATE brotlidec brotlienc brotlicommon)

set(BROTLI_ENABLED On) # Complete the "libraries_config.hpp" file
