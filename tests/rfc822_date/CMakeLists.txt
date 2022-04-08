# We might support earlier versions, too, but try to use a recent one.
cmake_minimum_required (VERSION 3.8)

project(rfc822date_test)

set(rfc822date_sources
    ../../src/StringFunctions.cpp
    ../../src/rfc822/Date.cpp
    rfc822_date.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions(-Wall -fexceptions)
endif ()
if (CODE_COVERAGE)
    add_definitions (-O0)
else()
    add_definitions (-O3)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(rfc822date_test ${rfc822date_sources})


# add executable as test
add_test(NAME test_rfc822date
         COMMAND $<TARGET_FILE:rfc822date_test>)
