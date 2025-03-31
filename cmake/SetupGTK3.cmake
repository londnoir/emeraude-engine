if ( NOT GTK3_ENABLED )
    message("Enabling GTK3 library from system (Linux) ...")

    find_package(PkgConfig REQUIRED)

    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

    target_include_directories(${PROJECT_NAME} PRIVATE ${GTK3_INCLUDE_DIRS})
    target_link_directories(${PROJECT_NAME} PRIVATE ${GTK3_LIBRARY_DIRS})
    #target_compile_definitions(${PROJECT_NAME} PRIVATE ${GTK3_CFLAGS_OTHER})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${GTK3_LIBRARIES})

    set(GTK3_ENABLED On)
else ()
    message("The GTK3 library is already enabled.")
endif ()