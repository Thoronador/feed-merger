cmake_minimum_required (VERSION 3.8...3.31)

# Recurse into subdirectory for tests of category parsing.
add_subdirectory (category)

# Recurse into subdirectory for tests of link parsing.
add_subdirectory (link)

# Recurse into subdirectory for tests of Person Construct parsing.
add_subdirectory (person-construct)
