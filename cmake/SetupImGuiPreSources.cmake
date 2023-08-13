if ( ENABLE_IMGUI )
	set(IMGUI_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/imgui)

	list(APPEND SOURCE_FILES
		${IMGUI_INCLUDE_DIRS}imgui.cpp
		${IMGUI_INCLUDE_DIRS}imgui_demo.cpp
		${IMGUI_INCLUDE_DIRS}imgui_draw.cpp
		${IMGUI_INCLUDE_DIRS}imgui_tables.cpp
		${IMGUI_INCLUDE_DIRS}imgui_widgets.cpp
		${IMGUI_INCLUDE_DIRS}backends/imgui_impl_glfw.cpp
		${IMGUI_INCLUDE_DIRS}backends/imgui_impl_vulkan.cpp
	)
endif ()
