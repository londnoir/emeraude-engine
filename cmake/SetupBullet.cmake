find_package(Bullet REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC ${BULLET_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PUBLIC ${BULLET_LIBRARIES})

message("Bullet library enabled !")
message(" - Headers : ${BULLET_INCLUDE_DIRS}")
message(" - Libraries : ${BULLET_LIBRARIES}")

set(BULLET_ENABLED On) # Complete the "libraries_config.hpp" file
