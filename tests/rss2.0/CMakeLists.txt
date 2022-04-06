# We might support earlier versions, too, but try to use a recent one.
cmake_minimum_required (VERSION 3.8)

# Recurse into subdirectory for tests of Parser class.
add_subdirectory (parser)

# Recurse into subdirectory for tests of Writer class.
add_subdirectory (writer)
