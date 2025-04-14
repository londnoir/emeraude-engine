message("Enabling JsonCpp library from local source ...")

target_include_directories(${PROJECT_NAME} PUBLIC ${JSONCPP_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PUBLIC JSON_USE_EXCEPTION=Off)

set(JSONCPP_ENABLED On)
