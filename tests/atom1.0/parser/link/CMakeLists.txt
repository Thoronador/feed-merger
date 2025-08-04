cmake_minimum_required (VERSION 3.8...3.31)

project(atom10-parse-link-test)

set(atom10-parse-link-test_sources
    ../../../../src/StringFunctions.cpp
    ../../../../src/atom1.0/Category.cpp
    ../../../../src/atom1.0/Link.cpp
    ../../../../src/atom1.0/Parser.cpp
    ../../../../src/atom1.0/PersonConstruct.cpp
    ../../../../src/xml/XMLDocument.cpp
    ../../../../src/xml/XMLNode.cpp
    main.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions(-Wall -Wextra -Wpedantic -Wshadow -fexceptions)
endif ()
if (CODE_COVERAGE)
    add_definitions (-O0)
else()
    add_definitions (-O3)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(atom10-parse-link-test ${atom10-parse-link-test_sources})

# find libxml2
find_package (LibXml2)
if (LibXml2_FOUND)
  include_directories(${LIBXML2_INCLUDE_DIRS})
  target_link_libraries (atom10-parse-link-test ${LIBXML2_LIBRARIES})
else ()
  message ( FATAL_ERROR "libxml2 was not found!" )
endif (LibXml2_FOUND)


# add executable as test
add_test(NAME Atom1.0_parseLink
         COMMAND $<TARGET_FILE:atom10-parse-link-test> ${CMAKE_CURRENT_SOURCE_DIR})
