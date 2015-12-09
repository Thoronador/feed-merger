# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

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

if (CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -O3 -fexceptions)
endif (CMAKE_COMPILER_IS_GNUCC)

add_definitions(-Wall -std=c++0x)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(atom10-parse-link-test ${atom10-parse-link-test_sources})

# find libxml2
set(LIBXML2_DIR "../../../../cmake/" )
find_package (LIBXML2)
if (LIBXML2_FOUND)
  include_directories(${LIBXML2_INCLUDE_DIRS})
  target_link_libraries (atom10-parse-link-test ${LIBXML2_LIBRARIES})
else ()
  message ( FATAL_ERROR "libxml2 was not found!" )
endif (LIBXML2_FOUND)


# add executable as test
add_test(NAME Atom1.0_parseLink
         COMMAND $<TARGET_FILE:atom10-parse-link-test> ${CMAKE_CURRENT_SOURCE_DIR})
