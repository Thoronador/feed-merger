# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

project(rss20-writer-generic-test)

set(rss20-writer-generic-test_sources
    ../../../../src/rfc822/Date.cpp
    ../../../../src/rss2.0/Category.cpp
    ../../../../src/rss2.0/Channel.cpp
    ../../../../src/rss2.0/Cloud.cpp
    ../../../../src/rss2.0/Days.cpp
    ../../../../src/rss2.0/Enclosure.cpp
    ../../../../src/rss2.0/Guid.cpp
    ../../../../src/rss2.0/Image.cpp
    ../../../../src/rss2.0/Item.cpp
    ../../../../src/rss2.0/Source.cpp
    ../../../../src/rss2.0/TextInput.cpp
    ../../../../src/rss2.0/Writer.cpp
    ../../../../src/StringFunctions.cpp
    main.cpp)

if (CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -O3 -fexceptions)
endif (CMAKE_COMPILER_IS_GNUCC)

add_definitions(-Wall -std=c++0x)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(rss20-writer-generic-test ${rss20-writer-generic-test_sources})

# find libxml2
set(LIBXML2_DIR "../../../../cmake/" )
find_package (LIBXML2)
if (LIBXML2_FOUND)
  include_directories(${LIBXML2_INCLUDE_DIRS})
  target_link_libraries (rss20-writer-generic-test ${LIBXML2_LIBRARIES})
else ()
  message ( FATAL_ERROR "libxml2 was not found!" )
endif (LIBXML2_FOUND)


# add executable as test
add_test(NAME RSS2.0_writeGeneric
         COMMAND $<TARGET_FILE:rss20-writer-generic-test>)
