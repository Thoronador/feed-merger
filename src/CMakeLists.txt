# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

project(feed-merger)

set(feed_merger_sources
    StringFunctions.cpp
    rfc822/Date.cpp
    rss2.0/Category.cpp
    rss2.0/Enclosure.cpp
    rss2.0/Guid.cpp
    main.cpp)

if (CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -O3 -fexceptions)
endif (CMAKE_COMPILER_IS_GNUCC)

add_definitions(-Wall -std=c++0x)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(feed-merger ${feed_merger_sources})
