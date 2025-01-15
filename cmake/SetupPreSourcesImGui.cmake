message("Enabling ImGUI library from local source ...")

set(IMGUI_VERSION "1.9.7git")
set(IMGUI_INCLUDE_DIRS ${LOCAL_LIB_DIR}/dependencies/imgui)
set(IMGUI_SOURCE_FILES
	${IMGUI_INCLUDE_DIRS}imgui.cpp
	${IMGUI_INCLUDE_DIRS}imgui_demo.cpp
	${IMGUI_INCLUDE_DIRS}imgui_draw.cpp
	${IMGUI_INCLUDE_DIRS}imgui_tables.cpp
	${IMGUI_INCLUDE_DIRS}imgui_widgets.cpp
	${IMGUI_INCLUDE_DIRS}backends/imgui_impl_glfw.cpp
	${IMGUI_INCLUDE_DIRS}backends/imgui_impl_vulkan.cpp
)