# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

# Recurse into subdirectory for test of parsing a simple feed.
add_subdirectory (spec-example-simple)

# Recurse into subdirectory for test of parsing more complete feed.
add_subdirectory (spec-example-complete)
