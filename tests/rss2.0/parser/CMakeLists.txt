# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

# Recurse into subdirectory for tests of parsing of minimized specification
# sample file.
add_subdirectory (min-spec-sample)

# Recurse into subdirectory for tests of parsing of specification sample file.
add_subdirectory (spec-sample)

# Recurse into subdirectory for tests of parsing of tumblr sample file.
add_subdirectory (devops-sample)

# Recurse into subdirectory for test of parsing <cloud> element of <channel>.
add_subdirectory (cloud-channel-element)

# Recurse into subdirectory for test of parsing <image> element of <channel>.
add_subdirectory (image-element)

# Recurse into subdirectory for test of parsing <enclosure> element of <item>.
add_subdirectory (enclosure-element)

# Recurse into subdirectory for test of parsing <source> element of <item>.
add_subdirectory (source-element)

# Recurse into subdirectory for test of parsing <category> element of <item>.
add_subdirectory (category-element)

# Recurse into subdirectory for test of parsing <category> element of <item>,
# but without the optional domain attribute.
add_subdirectory (category-element-nd)

# Recurse into subdirectory for test of parsing <category> element of <channel>.
add_subdirectory (category-element-channel)

# Recurse into subdirectory for test of parsing <textInput> element of <channel>.
add_subdirectory (textinput-element)
