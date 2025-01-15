message("Enabling ImGUI library (Local binary) ...")
message(" - Headers : ${IMGUI_INCLUDE_DIRS}")

target_include_directories(${PROJECT_NAME} PUBLIC ${IMGUI_INCLUDE_DIRS})

set(IMGUI_ENABLED On) # Complete the "emeraude_config.hpp" file
