# Vulkan library (Official CMAKE module)

if ( USE_SYSTEM_LIBRARIES )
	message("Using system GLSLang library.")

	find_package(Vulkan REQUIRED COMPONENTS glslangValidator glslang SPIRV-Tools)

	if ( Vulkan_FOUND )
		message("Vulkan ${Vulkan_VERSION} library found !")
		message(" - Headers : ${Vulkan_INCLUDE_DIRS}")
		message(" - Binary : ${Vulkan_LIBRARIES}")
		message(" - SDK : ${VULKAN_SDK}")

		target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIRS})
		target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_LIBRARIES})

		if ( Vulkan_glslc_FOUND )
			message("Vulkan glslc found !")
			message(" - Executable : ${Vulkan_GLSLC_EXECUTABLE}")
		endif ()

		if ( Vulkan_glslangValidator_FOUND )
			message("Vulkan glslangValidator found !")
			message(" - Executable : ${Vulkan_GLSLANG_VALIDATOR_EXECUTABLE}")
		endif ()

		if ( Vulkan_dxc_exe_FOUND )
			message("Vulkan dxc executable found !")
			message(" - Executable : ${Vulkan_dxc_EXECUTABLE}")
		endif ()

		if ( Vulkan_glslang_FOUND )
			message("Vulkan glslang found !")
			message(" - Binary : ${Vulkan_glslang_LIBRARY}")

			target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_glslang_LIBRARY} MachineIndependent OGLCompiler GenericCodeGen OSDependent glslang)
		endif ()

		if ( Vulkan_SPIRV-Tools_FOUND )
			message("Vulkan SPIRV-Tools found !")
			message(" - Binary : ${Vulkan_SPIRV-Tools_LIBRARY}")

			target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_SPIRV-Tools_LIBRARY} SPIRV SPIRV-Tools-opt SPIRV-Tools-reduce SPIRV-Tools-link SPIRV-Tools)
		endif ()

		if ( Vulkan_shaderc_combined_FOUND )
			message("Vulkan shaderc_combined found !")
			message(" - Binary : ${Vulkan_shaderc_combined_LIBRARY}")

			target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_shaderc_combined_LIBRARY})
		endif ()

		if ( Vulkan_MoltenVK_FOUND )
			message("Vulkan MoltenVK found !")
			message(" - Binary : ${Vulkan_MoltenVK_LIBRARY}")

			target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_MoltenVK_LIBRARY})
		endif ()

		if ( Vulkan_dxc_lib_FOUND )
			message("Vulkan dxc library found !")
			message(" - Binary : ${Vulkan_dxc_LIBRARY}")

			target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_dxc_LIBRARY})
		endif ()
	endif ()
else ()
	message("Using embedded GLSLang library.")

	find_package(Vulkan REQUIRED)

	message("Vulkan ${Vulkan_VERSION} library found !")
	message(" - Headers : ${Vulkan_INCLUDE_DIRS}")
	message(" - Binary : ${Vulkan_LIBRARIES}")
	message(" - SDK : ${VULKAN_SDK}")

	target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_LIBRARIES})

	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glslang glslang EXCLUDE_FROM_ALL)
	target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glslang/glslang/Include)
	target_link_libraries(${PROJECT_NAME} PRIVATE glslang SPIRV)
endif ()
