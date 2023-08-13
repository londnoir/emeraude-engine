# JsonCpp (Post sources configuration)

if ( USE_SYSTEM_LIBRARIES )
	message("Using system JsonCpp library.")

	find_package(JsonCpp REQUIRED)

	if ( JSONCPP_FOUND )
		message("JsonCpp library found !")
		message(" - Headers : ${JSONCPP_INCLUDE_DIRS}")
		message(" - Binary : ${JSONCPP_LIBRARY}")

		target_include_directories(${PROJECT_NAME} PUBLIC ${JSONCPP_INCLUDE_DIRS})
		target_link_libraries(${PROJECT_NAME} PUBLIC ${JSONCPP_LIBRARY})
	endif ()
else ()
	message("Using embedded JsonCpp library.")

	target_include_directories(${PROJECT_NAME} PUBLIC ${JSONCPP_INCLUDE_DIRS})
	target_compile_definitions(${PROJECT_NAME} PRIVATE JSON_USE_EXCEPTION=Off)
endif ()
