message("Enabling GTK3 library from system (Linux) ...")

find_package(PkgConfig REQUIRED)

pkg_check_modules(PC_GTK3 REQUIRED gtk+-3.0)

message("GTK3 ${PC_GTK3_VERSION} library enabled !")
message(" - Headers : ${PC_GTK3_INCLUDE_DIRS}")
message(" - Libraries : ${PC_GTK3_LIBRARIES}")
message(" - Binary : ${PC_GTK3_LIBRARIES}")

target_include_directories(${PROJECT_NAME} PRIVATE ${PC_GTK3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PC_GTK3_LIBRARIES})

set(GTK3_ENABLED On) # Complete the "libraries_config.hpp" file
