cmake_minimum_required (VERSION 3.8...3.31)

project(rss20-category-element-multiple-test)

set(rss20-category-element-multiple-test_sources
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
    ../../../../src/rss2.0/Protocol.cpp
    ../../../../src/rss2.0/Source.cpp
    ../../../../src/StringFunctions.cpp
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

add_executable(rss20-category-element-multiple-test ${rss20-category-element-multiple-test_sources})

# find libxml2
set(LIBXML2_DIR "../../../../cmake/" )
find_package (LIBXML2)
if (LIBXML2_FOUND)
  include_directories(${LIBXML2_INCLUDE_DIRS})
  target_link_libraries (rss20-category-element-multiple-test ${LIBXML2_LIBRARIES})
else ()
  message ( FATAL_ERROR "libxml2 was not found!" )
endif (LIBXML2_FOUND)


# add executable as test
add_test(NAME RSS2.0_parseMultipleCategoryElements
         COMMAND $<TARGET_FILE:rss20-category-element-multiple-test> ${CMAKE_CURRENT_SOURCE_DIR}/category-multi-rss-2.xml)
