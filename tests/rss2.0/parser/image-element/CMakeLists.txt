# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

project(rss20-image-element-test)

set(rss20-image-element-test_sources
    ../../../../src/basic-rss/Channel.cpp
    ../../../../src/basic-rss/Image.cpp
    ../../../../src/basic-rss/Parser.cpp
    ../../../../src/basic-rss/TextInput.cpp
    ../../../../src/rfc822/Date.cpp
    ../../../../src/rss2.0/Category.cpp
    ../../../../src/rss2.0/Channel.cpp
    ../../../../src/rss2.0/Cloud.cpp
    ../../../../src/rss2.0/Enclosure.cpp
    ../../../../src/rss2.0/Guid.cpp
    ../../../../src/rss2.0/Item.cpp
    ../../../../src/rss2.0/Parser.cpp
    ../../../../src/rss2.0/Source.cpp
    ../../../../src/StringFunctions.cpp
    ../../../../src/xml/XMLDocument.cpp
    ../../../../src/xml/XMLNode.cpp
    main.cpp)

if (CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -O3 -fexceptions)
endif (CMAKE_COMPILER_IS_GNUCC)

add_definitions(-Wall -std=c++0x)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(rss20-image-element-test ${rss20-image-element-test_sources})

# find libxml2
set(LIBXML2_DIR "../../../../cmake/" )
find_package (LIBXML2)
if (LIBXML2_FOUND)
  include_directories(${LIBXML2_INCLUDE_DIRS})
  target_link_libraries (rss20-image-element-test ${LIBXML2_LIBRARIES})
else ()
  message ( FATAL_ERROR "libxml2 was not found!" )
endif (LIBXML2_FOUND)


# add executable as test
add_test(NAME RSS2.0_parseChannelImageElement
         COMMAND $<TARGET_FILE:rss20-image-element-test> ${CMAKE_CURRENT_SOURCE_DIR}/image-element-rss-2.xml)
