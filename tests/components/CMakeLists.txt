# We might support earlier versions, too, but try to use a more recent one.
cmake_minimum_required (VERSION 3.8)

# test binary for components and functions
project(feed_merger_tests)

set(feed_merger_tests_sources
    ../../src/basic-rss/Days.cpp
    ../../src/rss2.0/Category.cpp
    ../../src/rss2.0/Cloud.cpp
    ../../src/rss2.0/Enclosure.cpp
    ../../src/rss2.0/Guid.cpp
    ../../src/rss2.0/Protocol.cpp
    ../../src/rss2.0/Source.cpp
    basic-rss/Days.cpp
    rss2.0/Category.cpp
    rss2.0/Cloud.cpp
    rss2.0/Enclosure.cpp
    rss2.0/Guid.cpp
    rss2.0/Protocol.cpp
    rss2.0/Source.cpp
    main.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions (-Wall -Wextra -pedantic -fexceptions)
endif ()
if (CODE_COVERAGE)
    add_definitions (-O0)
else()
    add_definitions (-O2)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )
add_executable(feed_merger_tests ${feed_merger_tests_sources})

# add test case
add_test(NAME component_tests
         COMMAND $<TARGET_FILE:feed_merger_tests>)
