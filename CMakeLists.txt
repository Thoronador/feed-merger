# We might support earlier versions, too, but try to use a recent one.
cmake_minimum_required (VERSION 3.8)

project(feed-merger)

# Recurse into the subdirectory for source code.
add_subdirectory (src)

enable_testing()

# Recurse into the subdirectory for tests.
add_subdirectory (tests)
