# We might support earlier versions, too, but try to use a recent one.
cmake_minimum_required (VERSION 3.8)

# Recurse into subdirectory for test of parsing a simple feed.
add_subdirectory (spec-example-simple)

# Recurse into subdirectory for test of parsing more complete feed.
add_subdirectory (spec-example-complete)
