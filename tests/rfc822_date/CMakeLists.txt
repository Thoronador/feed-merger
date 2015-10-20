# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

project(rfc822date_test)

set(rfc822date_sources
    ../../src/StringFunctions.cpp
    ../../src/rfc822/Date.cpp
    main.cpp)

if (CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -O3 -fexceptions)
endif (CMAKE_COMPILER_IS_GNUCC)

add_definitions(-Wall -std=c++0x)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(rfc822date_test ${rfc822date_sources})


# add executable as test
add_test(NAME test_rfc822date
         COMMAND $<TARGET_FILE:rfc822date_test>)
