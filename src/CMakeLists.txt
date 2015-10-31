# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

project(feed-merger)

set(feed_merger_sources
    Curly.cpp
    StringFunctions.cpp
    rfc822/Date.cpp
    rss2.0/Category.cpp
    rss2.0/Channel.cpp
    rss2.0/Cloud.cpp
    rss2.0/Enclosure.cpp
    rss2.0/Guid.cpp
    rss2.0/Image.cpp
    rss2.0/Item.cpp
    rss2.0/Parser.cpp
    rss2.0/Source.cpp
    rss2.0/TextInput.cpp
    xml/XMLDocument.cpp
    xml/XMLNode.cpp
    main.cpp)

if (CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -O3 -fexceptions)
endif (CMAKE_COMPILER_IS_GNUCC)

add_definitions(-Wall -std=c++0x)

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
