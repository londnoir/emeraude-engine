message("Configuring reproc/reproc++ library as sub-project ...")

set(REPROC++ ON)
set(REPROC_MULTITHREADED ON)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/reproc EXCLUDE_FROM_ALL)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/reproc/reproc/include
        ${CMAKE_CURRENT_SOURCE_DIR}/reproc/reproc++/include
)
target_link_libraries(${PROJECT_NAME} PRIVATE reproc reproc++)
