# https://github.com/google/googletest/blob/master/googletest/README.md

if (NOT EXISTS ${SCRIPTX_TEST_GOOGLE_TEST})
    # Download and unpack googletest at configure time
    configure_file(${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt.in googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
    if (result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif ()

    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
    if (result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif ()
elseif (("${SCRIPTX_TEST_FORCE_UPDATE_DEPS}" STREQUAL ON) OR ("$ENV{SCRIPTX_TEST_FORCE_UPDATE_DEPS}" STREQUAL ON))
    message(STATUS "update SCRIPTX_TEST_GOOGLE_TEST ${SCRIPTX_TEST_GOOGLE_TEST}")
    execute_process(COMMAND git pull --force --rebase WORKING_DIRECTORY ${SCRIPTX_TEST_GOOGLE_TEST})
endif ()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${SCRIPTX_TEST_GOOGLE_TEST}
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif ()
