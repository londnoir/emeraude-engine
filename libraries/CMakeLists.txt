###### CMake configuration ######

cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

project(EmeraudeLibraries VERSION 1.2.0 DESCRIPTION "Emeraude engine libraries" LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE On)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG")
set_property(GLOBAL PROPERTY USE_FOLDERS On)

# Adds custom CMake scripts/modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../cmake)

# Project options
set(ENABLE_CROSS_PLATFORM_WARNINGS_MANAGEMENT Off CACHE BOOL "Hide warnings produced by third-party libraries.")
set(USE_SYSTEM_LIBRARIES On CACHE BOOL "Try to use system libraries.")
set(ENABLE_LIBRARIES_TESTING Off CACHE BOOL "Enable testing suite.")
set(DEBUG_OBSERVER_PATTERN Off CACHE BOOL "Enable the debug output of observer pattern.")
set(DEBUG_PIXEL_FACTORY Off CACHE BOOL "Enable the debug output of pixel factory library.")
set(DEBUG_VERTEX_FACTORY Off CACHE BOOL "Enable the debug output of vertex factory library.")
set(DEBUG_WAVE_FACTORY Off CACHE BOOL "Enable the debug output of wave factory library.")
set(INTERNET_CHECK_DOMAIN "google.com" CACHE STRING "Web domain to check internet connexion.")

set(ENABLE_ZLIB On CACHE BOOL "Enable ZLib library.")
set(ENABLE_JPEG On CACHE BOOL "Enable Jpeg library.")
set(ENABLE_PNG On CACHE BOOL "Enable Png library.")
set(ENABLE_FREETYPE On CACHE BOOL "Enable FreeType library. Adds the ability to read font file.")
set(ENABLE_SNDFILE On CACHE BOOL "Enable SndFile library. Adds the ability to read a wide range of sound formats.")
set(ENABLE_SAMPLERATE On CACHE BOOL "Enable SampleRate library. Adds the ability to resample a sound on the fly to meet OpenAL settings.")
set(ENABLE_GLM Off CACHE BOOL "Enable GLM library. Adds an alternate math library.")
set(ENABLE_EIGEN Off CACHE BOOL "Enable Eigen library. Adds an alternate math library.")
set(ENABLE_ASIO On CACHE BOOL "Enable ASIO library. Adds the networking ability.")

# Create constant variable for dependency inclusions
get_filename_component(TEMP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
set(LIBRARIES_INCLUDE_DIR ${TEMP_INCLUDE_DIR} CACHE STRING "Libraries include directory.")

# Print out project paths
message("[${PROJECT_NAME}] Project directory : ${CMAKE_SOURCE_DIR}, current : ${CMAKE_CURRENT_SOURCE_DIR}")
message("[${PROJECT_NAME}] Source directory : ${LIBRARIES_INCLUDE_DIR}")
message("[${PROJECT_NAME}] Binary directory : ${CMAKE_BINARY_DIR}, current : ${CMAKE_CURRENT_BINARY_DIR}")
message("[${PROJECT_NAME}] Install directory : ${CMAKE_INSTALL_PREFIX}")



###### Project configuration ######

# Root header files
file(GLOB LIBRARIES_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

# Root source files
file(GLOB LIBRARIES_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Add project directories to find all header/source files.
set(
	LIBRARIES_DIRECTORIES
	${CMAKE_CURRENT_SOURCE_DIR}/GameTools
	${CMAKE_CURRENT_SOURCE_DIR}/Hash
	${CMAKE_CURRENT_SOURCE_DIR}/KVParser
	${CMAKE_CURRENT_SOURCE_DIR}/Math
	${CMAKE_CURRENT_SOURCE_DIR}/Network
	${CMAKE_CURRENT_SOURCE_DIR}/Path
	${CMAKE_CURRENT_SOURCE_DIR}/PixelFactory
	${CMAKE_CURRENT_SOURCE_DIR}/Third-Party-Inclusion
	${CMAKE_CURRENT_SOURCE_DIR}/Time
	${CMAKE_CURRENT_SOURCE_DIR}/VertexFactory
	${CMAKE_CURRENT_SOURCE_DIR}/WaveFactory
)

foreach ( LIBRARIES_DIRECTORY ${LIBRARIES_DIRECTORIES} )
	# Append sub-directory header files
	file(GLOB_RECURSE LIBRARIES_DIRECTORY_HEADER_FILES ${LIBRARIES_DIRECTORY}/*.hpp)
	list (APPEND LIBRARIES_HEADER_FILES ${LIBRARIES_DIRECTORY_HEADER_FILES})

	# Append sub-directory source files
	file(GLOB_RECURSE LIBRARIES_DIRECTORY_SOURCE_FILES ${LIBRARIES_DIRECTORY}/*.cpp)
	list (APPEND LIBRARIES_SOURCE_FILES ${LIBRARIES_DIRECTORY_SOURCE_FILES})
endforeach ()

include(SetupJsonCppPreSources)
add_library(${PROJECT_NAME} STATIC ${LIBRARIES_SOURCE_FILES})
target_sources(${PROJECT_NAME} PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} FILES ${LIBRARIES_HEADER_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED On
	CXX_EXTENSIONS On # "c++20" -> "gnu++20"
	VERSION ${PROJECT_VERSION}
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
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(${PROJECT_NAME} PUBLIC ENABLE_CROSS_PLATFORM_WARNINGS_MANAGEMENT=On)


###### Dependencies ######

include(SetupJsonCppPostSources)

include(SetupZLIB)

include(SetupJPEG)

include(SetupPNG)

include(SetupFreetype)

include(SetupSndFile)

include(SetupSamplerate)

include(SetupGLM)

include(SetupASIO)



###### Write the project C++ config file ######

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libraries_config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/libraries_config.hpp)



###### Testing ######

if ( ENABLE_LIBRARIES_TESTING )
	file(GLOB_RECURSE TEST_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Testing/*.cpp)

	add_executable(EmeraudeLibrariesTest ${TEST_SOURCE_FILES})
	target_include_directories(EmeraudeLibrariesTest PRIVATE ${LIBRARIES_INCLUDE_DIR})
	target_link_libraries(EmeraudeLibrariesTest PRIVATE ${PROJECT_NAME})

	# Enabling google test as sub project
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

	add_subdirectory(${CMAKE_SOURCE_DIR}/../dependencies/googletest gtest)
	target_link_libraries(EmeraudeLibrariesTest PRIVATE gtest)
	target_include_directories(EmeraudeLibrariesTest PRIVATE ${CMAKE_SOURCE_DIR}/../dependencies/googletest)

	enable_testing()

	add_test(NAME EmeraudeLibrariesTest COMMAND $<TARGET_FILE:EmeraudeLibrariesTest>)
endif ()


