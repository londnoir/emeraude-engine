message("Enabling JsonCpp library from local source ...")

if ( NOT EXISTS ${LOCAL_LIB_DIR}/include/json )
	set(JSONCPP_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/jsoncpp)

	find_package(Python3 REQUIRED COMPONENTS Interpreter)

	execute_process(
		COMMAND ${Python3_EXECUTABLE} amalgamate.py --source ${LOCAL_LIB_DIR}/include/jsoncpp.cpp
		WORKING_DIRECTORY ${JSONCPP_SOURCE_DIR}
		COMMAND_ERROR_IS_FATAL ANY
	)
endif ()

set(JSONCPP_VERSION "1.9.7git")
set(JSONCPP_INCLUDE_DIRS ${LOCAL_LIB_DIR}/include)
set(JSONCPP_HEADER_FILES ${LOCAL_LIB_DIR}/include/json/json.h ${LOCAL_LIB_DIR}/include/json/json-forwards.h)
set(JSONCPP_SOURCE_FILES ${LOCAL_LIB_DIR}/include/jsoncpp.cpp)

message("JsonCpp ${JSONCPP_VERSION} library enabled !")
message(" - Headers : ${JSONCPP_INCLUDE_DIRS}")
message(" - Libraries : None")
message(" - Binary : None")
