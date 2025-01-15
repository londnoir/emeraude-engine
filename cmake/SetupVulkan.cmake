message("Enabling Vulkan library from system ...")

if ( MSVC )
	set(ENV{VULKAN_SDK} "C:/VulkanSDK/1.4.304.0/")
endif ()

find_package(Vulkan REQUIRED)

message("Vulkan ${Vulkan_VERSION} library enabled !")
message(" - Headers : ${Vulkan_INCLUDE_DIRS}")
message(" - Binary : ${Vulkan_LIBRARIES}")
message(" - SDK : ${VULKAN_SDK}")

target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${Vulkan_LIBRARIES})
