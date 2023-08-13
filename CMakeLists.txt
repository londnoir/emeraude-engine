###### CMake configuration ######

cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

project(Emeraude VERSION 0.7.0 DESCRIPTION "Open-Source 3D Graphics Engine." LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE Off)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG")
set_property(GLOBAL PROPERTY USE_FOLDERS On)

# Adds custom CMake scripts/modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# Project options
set(ENABLE_SHARED_LIBRARY On CACHE BOOL "Enable emeraude as a shared library.")
set(INSTALL_DEV Off CACHE BOOL "Installs dev files.")
set(ENABLE_CROSS_PLATFORM_WARNINGS_MANAGEMENT Off CACHE BOOL "Hide warnings produced by third-party libraries.")
set(USE_SYSTEM_LIBRARIES On CACHE BOOL "Try to use system libraries.")
set(ENABLE_EMERAUDE_TESTING Off CACHE BOOL "Enable emeraude testing suite.")
set(DEBUG_INPUT_LAYER Off CACHE BOOL "Enable the debug for input layer.")
set(ENABLE_OPENAL On CACHE BOOL "Enable OpenAL library. Adds the audio to the engine.")
set(ENABLE_AUBIO Off CACHE BOOL "Enable Aubio library. Adds the ability to analyze sound.")
set(ENABLE_TAGLIB Off CACHE BOOL "Enable TagLib library. Adds the ability to read media file tags.")
set(ENABLE_IMGUI Off CACHE BOOL "Enable Dear ImGui library. Adds a GUI to the engine.")

# Create constant variable for dependency inclusions
get_filename_component(TEMP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src ABSOLUTE)
set(EMERAUDE_INCLUDE_DIR ${TEMP_INCLUDE_DIR} CACHE STRING "Emeraude engine include directory.")

# Print out project paths
message("[${PROJECT_NAME}] Project directory : ${CMAKE_SOURCE_DIR}, current : ${CMAKE_CURRENT_SOURCE_DIR}")
message("[${PROJECT_NAME}] Source directory : ${EMERAUDE_INCLUDE_DIR}")
message("[${PROJECT_NAME}] Binary directory : ${CMAKE_BINARY_DIR}, current : ${CMAKE_CURRENT_BINARY_DIR}")
message("[${PROJECT_NAME}] Install directory : ${CMAKE_INSTALL_PREFIX}")


###### Project configuration ######

# Root header files
file(GLOB EMERAUDE_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)

# Root source files
file(GLOB EMERAUDE_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Add project directories to find all header/source files.
set(
	EMERAUDE_DIRECTORIES
	${CMAKE_CURRENT_SOURCE_DIR}/src/Animations
	${CMAKE_CURRENT_SOURCE_DIR}/src/Audio
	${CMAKE_CURRENT_SOURCE_DIR}/src/Dev
	${CMAKE_CURRENT_SOURCE_DIR}/src/Graphics
	${CMAKE_CURRENT_SOURCE_DIR}/src/Input
	${CMAKE_CURRENT_SOURCE_DIR}/src/MasterControl
	${CMAKE_CURRENT_SOURCE_DIR}/src/Overlay
	${CMAKE_CURRENT_SOURCE_DIR}/src/Physics
	${CMAKE_CURRENT_SOURCE_DIR}/src/Resources
	${CMAKE_CURRENT_SOURCE_DIR}/src/Saphir
	${CMAKE_CURRENT_SOURCE_DIR}/src/Scenes
	${CMAKE_CURRENT_SOURCE_DIR}/src/Third-Party-Inclusion
	${CMAKE_CURRENT_SOURCE_DIR}/src/Tool
	${CMAKE_CURRENT_SOURCE_DIR}/src/Vulkan
)

foreach ( EMERAUDE_DIRECTORY ${EMERAUDE_DIRECTORIES} )
	# Append sub-directory header files
	file(GLOB_RECURSE EMERAUDE_DIRECTORY_HEADER_FILES ${EMERAUDE_DIRECTORY}/*.hpp)
	list (APPEND EMERAUDE_HEADER_FILES ${EMERAUDE_DIRECTORY_HEADER_FILES})

	# Append sub-directory source files
	file(GLOB_RECURSE EMERAUDE_DIRECTORY_SOURCE_FILES ${EMERAUDE_DIRECTORY}/*.cpp)
	list (APPEND EMERAUDE_SOURCE_FILES ${EMERAUDE_DIRECTORY_SOURCE_FILES})
endforeach ()

include(SetupImGuiPreSources)

if ( ENABLE_SHARED_LIBRARY )
	add_library(${PROJECT_NAME} SHARED ${EMERAUDE_SOURCE_FILES})
else ()
	add_library(${PROJECT_NAME} STATIC ${EMERAUDE_SOURCE_FILES})
endif ()

target_sources(${PROJECT_NAME} PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} FILES ${EMERAUDE_HEADER_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED On
	CXX_EXTENSIONS On # "c++20" -> "gnu++20"
	VERSION ${PROJECT_VERSION}
	SOVERSION 1
)
if ( MSVC )

else ()
	target_compile_options(${PROJECT_NAME} PRIVATE
		-fno-exceptions -fopenmp # Common flags
		-Wno-unknown-pragmas -Wno-unused # Disable some warnings
		$<$<CONFIG:Debug>:-DDEBUG -O0 -g -Wall -Wextra -Wpedantic> # Debug flags
		$<$<CONFIG:Relase>:-DNDEBUG -O2 -fdata-sections -ffunction-sections> # Release flags
	)

	if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
		target_compile_options(${PROJECT_NAME} PRIVATE -stdlib=libc+)
	endif ()
endif ()
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_definitions(${PROJECT_NAME} PUBLIC ENABLE_CROSS_PLATFORM_WARNINGS_MANAGEMENT=On)



###### Emeraude Libraries project ######

add_subdirectory(${CMAKE_SOURCE_DIR}/libraries EmeraudeLibraries)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBRARIES_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC EmeraudeLibraries)
if ( ENABLE_SHARED_LIBRARY )
	target_compile_options(EmeraudeLibraries PRIVATE -fPIC)
endif ()



###### Dependencies ######

include(SetupThreads)

include(SetupVulkan)

include(SetupOpenAL)

include(SetupGLFW3)

include(SetupAubio)

include(SetupTagLib)

include(SetupImGuiPostSources)



###### Write the project C++ config file ######

# Copy 'gamecontrollerdb.txt' in the compilation directory.
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL_GameControllerDB/gamecontrollerdb.txt DESTINATION ${CMAKE_BINARY_DIR}/data)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/emeraude_config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/src/emeraude_config.hpp)



###### Testing ######

if ( ENABLE_EMERAUDE_TESTING )
	file(GLOB_RECURSE TEST_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/Testing/*.cpp)

	add_executable(EmeraudeTest ${TEST_SOURCE_FILES})
	target_include_directories(EmeraudeTest PRIVATE ${EMERAUDE_INCLUDE_DIR})
	target_link_libraries(EmeraudeTest PRIVATE ${PROJECT_NAME})

	# Enabling google test as sub project
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

	add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/googletest gtest)
	target_link_libraries(EmeraudeTest PRIVATE gtest)
	target_include_directories(EmeraudeTest PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/googletest)

	enable_testing()

	add_test(NAME EmeraudeTest COMMAND $<TARGET_FILE:EmeraudeTest>)
endif ()



###### Installing ######

if ( UNIX AND NOT APPLE )
	if ( INSTALL_DEV )

		install(
			TARGETS EmeraudeLibraries
			LIBRARY DESTINATION lib
			ARCHIVE DESTINATION lib
			RUNTIME DESTINATION bin
			FILE_SET HEADERS DESTINATION include/EmeraudeLibraries
		)

		install(
			TARGETS ${PROJECT_NAME}
			LIBRARY DESTINATION lib
			ARCHIVE DESTINATION lib
			RUNTIME DESTINATION bin
			FILE_SET HEADERS DESTINATION include/${PROJECT_NAME}
		)

		install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION lib/pkgconfig)

	else ()

		install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)

	endif ()
endif ()


