cmake_minimum_required (VERSION 3.8...3.31)

project(feed-merger)

# option for code coverage
option(CODE_COVERAGE "Build with code coverage (GCC only)" OFF)
# If CODE_COVERAGE is on (e. g. via `cmake -DCODE_COVERAGE=ON`), then all
# binaries are built with code coverage. The option is off by default.
# Currently this only works with GCC.
if (CODE_COVERAGE)
  if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "Code coverage builds need GCC compiler!")
  endif ()
  # set coverage options for GCC
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
endif ()

# Recurse into the subdirectory for source code.
add_subdirectory (src)

enable_testing()

# Recurse into the subdirectory for tests.
add_subdirectory (tests)
