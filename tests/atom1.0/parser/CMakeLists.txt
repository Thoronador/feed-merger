# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

# Recurse into subdirectory for tests of category parsing.
add_subdirectory (category)

# Recurse into subdirectory for tests of link parsing.
add_subdirectory (link)

# Recurse into subdirectory for tests of Person Construct parsing.
add_subdirectory (person-construct)
