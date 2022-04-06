# We might support earlier versions, too, but try to use a recent one.
cmake_minimum_required (VERSION 3.8)

project(rss091-spec-sample-simple-test)

set(rss091-spec-sample-simple-test_sources
    ../../../../src/StringFunctions.cpp
    ../../../../src/basic-rss/Channel.cpp
    ../../../../src/basic-rss/Days.cpp
    ../../../../src/basic-rss/Image.cpp
    ../../../../src/basic-rss/Parser.cpp
    ../../../../src/basic-rss/TextInput.cpp
    ../../../../src/rfc822/Date.cpp
    ../../../../src/rss0.91/Channel.cpp
    ../../../../src/rss0.91/Item.cpp
    ../../../../src/rss0.91/Parser.cpp
    ../../../../src/xml/XMLDocument.cpp
    ../../../../src/xml/XMLNode.cpp
    main.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions(-Wall -O3 -fexceptions)
endif ()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(rss091-spec-sample-simple-test ${rss091-spec-sample-simple-test_sources})

# find libxml2
set(LIBXML2_DIR "../../../cmake/" )
find_package (LIBXML2)
if (LIBXML2_FOUND)
  include_directories(${LIBXML2_INCLUDE_DIRS})
  target_link_libraries (rss091-spec-sample-simple-test ${LIBXML2_LIBRARIES})
else ()
  message ( FATAL_ERROR "libxml2 was not found!" )
endif (LIBXML2_FOUND)


# add executable as test
add_test(NAME RSS0.91_parseSpecificationSampleSimple
         COMMAND $<TARGET_FILE:rss091-spec-sample-simple-test> ${CMAKE_CURRENT_SOURCE_DIR}/simple-example-rss-0.91.xml)
