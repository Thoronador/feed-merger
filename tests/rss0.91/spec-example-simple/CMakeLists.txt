cmake_minimum_required (VERSION 3.8...3.31)

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

add_executable(rss091-spec-sample-simple-test ${rss091-spec-sample-simple-test_sources})

# find libxml2
find_package (LibXml2)
if (LibXml2_FOUND)
  include_directories(${LIBXML2_INCLUDE_DIRS})
  target_link_libraries (rss091-spec-sample-simple-test ${LIBXML2_LIBRARIES})
else ()
  message ( FATAL_ERROR "libxml2 was not found!" )
endif (LibXml2_FOUND)


# add executable as test
add_test(NAME RSS0.91_parseSpecificationSampleSimple
         COMMAND $<TARGET_FILE:rss091-spec-sample-simple-test> ${CMAKE_CURRENT_SOURCE_DIR}/simple-example-rss-0.91.xml)
