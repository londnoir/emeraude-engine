message("Preparing JsonCpp library from local source ...")

set(JSONCPP_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/jsoncpp)
set(JSONCPP_TARGET_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/jsoncpp-amalgamated)

if ( NOT EXISTS ${JSONCPP_TARGET_DIR} )
	find_package(Python3 REQUIRED COMPONENTS Interpreter)

	execute_process(
		COMMAND ${Python3_EXECUTABLE} amalgamate.py --source ${JSONCPP_TARGET_DIR}/include/jsoncpp.cpp
		WORKING_DIRECTORY ${JSONCPP_SOURCE_DIR}
		COMMAND_ERROR_IS_FATAL ANY
	)
endif ()

set(JSONCPP_VERSION "1.9.7git")
set(JSONCPP_INCLUDE_DIRS ${JSONCPP_TARGET_DIR}/include)
set(JSONCPP_HEADER_FILES ${JSONCPP_TARGET_DIR}/include/json/json.h ${JSONCPP_TARGET_DIR}/include/json/json-forwards.h)
set(JSONCPP_SOURCE_FILES ${JSONCPP_TARGET_DIR}/include/jsoncpp.cpp)

message("JsonCpp ${JSONCPP_VERSION} library enabled !")
message(" - Headers : ${JSONCPP_INCLUDE_DIRS}")
message(" - Libraries : None")
message(" - Binary : None")
