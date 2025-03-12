message("Enabling cpu_features library from local source ...")

if ( MSVC )
	target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/cpu_features.lib)
else ()
	target_link_libraries(${PROJECT_NAME} PRIVATE ${LOCAL_LIB_DIR}/lib/libcpu_features.a)
endif ()

set(CPUFEATURES_ENABLED On) # Complete the "libraries_config.hpp" file
