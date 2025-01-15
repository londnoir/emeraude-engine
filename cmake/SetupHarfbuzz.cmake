message("Enabling Harfbuzz library from local source ...")

if ( NOT EXISTS ${LOCAL_LIB_DIR}/include/harfbuzz )
    set(HARFBUZZ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/harfbuzz)
    set(HARFBUZZ_BUILD_DIR ${TEMPORARY_BUILD_DIR}/harfbuzz-${CMAKE_BUILD_TYPE})

    if ( UNIX AND NOT APPLE )
        execute_process(
            COMMAND ${CMAKE_COMMAND}
            -S ${HARFBUZZ_SOURCE_DIR}
            -B ${HARFBUZZ_BUILD_DIR}
            -DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
            -DCMAKE_C_FLAGS=-fPIC
            -DCMAKE_CXX_FLAGS=-fPIC
            -DBUILD_SHARED_LIBS=Off
            ${CMAKE_GEN_EXTRA_FLAGS}
            COMMAND_ERROR_IS_FATAL ANY
        )
    elseif ( APPLE )
        execute_process(
            COMMAND ${CMAKE_COMMAND}
            -S ${HARFBUZZ_SOURCE_DIR}
            -B ${HARFBUZZ_BUILD_DIR}
            -DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
            -DCMAKE_C_FLAGS="-mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET} -fPIC"
            -DCMAKE_CXX_FLAGS="-mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET} -fPIC"
            -DBUILD_SHARED_LIBS=Off
            ${CMAKE_GEN_EXTRA_FLAGS}
            COMMAND_ERROR_IS_FATAL ANY
        )
    elseif ( MSVC )
        execute_process(
            COMMAND ${CMAKE_COMMAND}
            -S ${HARFBUZZ_SOURCE_DIR}
            -B ${HARFBUZZ_BUILD_DIR}
            -DCMAKE_INSTALL_PREFIX=${LOCAL_LIB_DIR}
            -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded$<$<CONFIG:Debug>:Debug>
            -DCMAKE_C_FLAGS_RELEASE="/MT" # Requested
            -DCMAKE_C_FLAGS_DEBUG="/MTd" # Requested
            -DCMAKE_CXX_FLAGS_RELEASE="/MT" # Requested
            -DCMAKE_CXX_FLAGS_DEBUG="/MTd" # Requested
            -DBUILD_SHARED_LIBS=Off
            ${CMAKE_GEN_EXTRA_FLAGS}
            COMMAND_ERROR_IS_FATAL ANY
        )
    else ()
        message(FATAL_ERROR "Unknown platform !")
    endif ()

    execute_process(COMMAND ${CMAKE_COMMAND} --build ${HARFBUZZ_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} --parallel ${CMAKE_BUILD_PARALLEL_LEVEL} COMMAND_ERROR_IS_FATAL ANY)

    execute_process(COMMAND ${CMAKE_COMMAND} --install ${HARFBUZZ_BUILD_DIR} --config ${CMAKE_BUILD_TYPE} COMMAND_ERROR_IS_FATAL ANY)
endif ()

set(HARFBUZZ_VERSION "10.1.0git")
set(HARFBUZZ_INCLUDE_DIRS ${LOCAL_LIB_DIR}/include)
set(HARFBUZZ_LIBRARY_DIRS ${LOCAL_LIB_DIR}/lib)
if ( MSVC )
    set(HARFBUZZ_LIBRARIES
        ${LOCAL_LIB_DIR}/lib/harfbuzz.lib
        ${LOCAL_LIB_DIR}/lib/harfbuzz-subset.lib
    )
else ()
    set(HARFBUZZ_LIBRARIES
        ${LOCAL_LIB_DIR}/lib/libharfbuzz.a
        ${LOCAL_LIB_DIR}/lib/libharfbuzz-subset.a
    )
endif ()

message("Harfbuzz ${HARFBUZZ_VERSION} library enabled !")
message(" - Headers : ${HARFBUZZ_INCLUDE_DIRS}")
message(" - Libraries : ${HARFBUZZ_LIBRARY_DIRS}")
message(" - Binary : ${HARFBUZZ_LIBRARIES}")

target_link_libraries(${PROJECT_NAME} PUBLIC ${HARFBUZZ_LIBRARIES})

set(HARFBUZZ_ENABLED On) # Complete the "libraries_config.hpp" file
