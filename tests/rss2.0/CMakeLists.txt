# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

# Recurse into subdirectory for tests of Parser class.
add_subdirectory (parser)

# Recurse into subdirectory for tests of Writer class.
add_subdirectory (writer)
