# JsonCpp (Pre sources configuration)

if ( NOT USE_SYSTEM_LIBRARIES )
	set(JSONCPP_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/jsoncpp-min/jsoncpp)

	if ( NOT EXISTS ${JSONCPP_INCLUDE_DIRS}/jsoncpp.cpp )
		message("Amalgamating JsonCpp to the project ...")

		find_package(Python3 REQUIRED COMPONENTS Interpreter)

		file(MAKE_DIRECTORY ${JSONCPP_INCLUDE_DIRS})

		execute_process(COMMAND ${Python3_EXECUTABLE} amalgamate.py --source ${JSONCPP_INCLUDE_DIRS}/jsoncpp.cpp WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/jsoncpp/ COMMAND_ERROR_IS_FATAL ANY)
	endif ()

	list(APPEND LIBRARIES_SOURCE_FILES ${JSONCPP_INCLUDE_DIRS}/jsoncpp.cpp)
endif ()
