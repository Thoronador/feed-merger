# We might support earlier versions, too, but try to use a recent one.
cmake_minimum_required (VERSION 3.8)

project(feed-merger)

set(feed_merger_sources
    Curly.cpp
    StringFunctions.cpp
    rfc822/Date.cpp
    atom1.0/Category.cpp
    atom1.0/Link.cpp
    atom1.0/Entry.cpp
    atom1.0/Parser.cpp
    atom1.0/PersonConstruct.cpp
    basic-rss/Channel.cpp
    basic-rss/Days.cpp
    basic-rss/Image.cpp
    basic-rss/Parser.cpp
    basic-rss/TextInput.cpp
    rss2.0/Category.cpp
    rss2.0/Channel.cpp
    rss2.0/Cloud.cpp
    rss2.0/Enclosure.cpp
    rss2.0/Guid.cpp
    rss2.0/Item.cpp
    rss2.0/Merger.cpp
    rss2.0/Parser.cpp
    rss2.0/Source.cpp
    rss2.0/Writer.cpp
    xml/XMLDocument.cpp
    xml/XMLNode.cpp
    main.cpp)

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

add_executable(feed-merger ${feed_merger_sources})

# find libxml2
set(LIBXML2_DIR "../cmake/" )
find_package (LIBXML2)
if (LIBXML2_FOUND)
  include_directories(${LIBXML2_INCLUDE_DIRS})
  target_link_libraries (feed-merger ${LIBXML2_LIBRARIES})
else ()
  message ( FATAL_ERROR "libxml2 was not found!" )
endif (LIBXML2_FOUND)

# find cURL library
find_package (CURL)
if (CURL_FOUND)
  include_directories(${CURL_INCLUDE_DIRS})
  target_link_libraries (feed-merger ${CURL_LIBRARIES})
else ()
  message ( FATAL_ERROR "cURL was not found!" )
endif (CURL_FOUND)
