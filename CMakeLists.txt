# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

# Recurse into the subdirectory for source code.
add_subdirectory (src)

enable_testing()

# Recurse into the subdirectory for tests.
add_subdirectory (tests)
