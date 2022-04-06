# We might support earlier versions, too, but try to use a more recent one.
cmake_minimum_required (VERSION 3.8)

enable_testing()

# Recurse into subdirectory for test of binary executable file.
add_subdirectory (feed-merger)

# Recurse into subdirectory for test of RFC 822 date stuff.
add_subdirectory (rfc822_date)

# Recurse into subdirectory for tests of RSS 0.91 classes.
add_subdirectory (rss0.91)

# Recurse into subdirectory for tests of RSS 2.0 classes.
add_subdirectory (rss2.0)

# Recurse into subdirectory for tests of Atom 1.0 classes.
add_subdirectory (atom1.0)
