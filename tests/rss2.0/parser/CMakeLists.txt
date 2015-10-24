# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

# Recurse into subdirectory for tests of parsing of minimized specification
# sample file.
add_subdirectory (min-spec-sample)

# Recurse into subdirectory for tests of parsing of specification sample file.
add_subdirectory (spec-sample)
