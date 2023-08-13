# ImGUI library (Optional)

if ( ENABLE_IMGUI )
	message("Enabling Dear ImGui library !")

        if ( USE_SYSTEM_LIBRARIES )
		message("Using system Dear ImGui library.")

	else ()
		message("Using embedded Dear ImGui library.")
		message(" - Headers : ${IMGUI_INCLUDE_DIRS}")

		target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_INCLUDE_DIRS})
	endif ()

	set(IMGUI_ENABLED On) # Complete the "emeraude_config.hpp" file
endif ()
