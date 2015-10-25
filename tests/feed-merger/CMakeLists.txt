# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

# ************************************
# * tests for feed-merger executable *
# ************************************

# add tests for --version and --help parameters
# default help parameter "--help"
add_test(NAME feed-merger_help
         COMMAND $<TARGET_FILE:feed-merger> --help)

# short help parameter with question mark "-?"
add_test(NAME feed-merger_help_question_mark
         COMMAND $<TARGET_FILE:feed-merger> -?)

# Windows-style help parameter "/?"
add_test(NAME feed-merger_help_question_mark_win
         COMMAND $<TARGET_FILE:feed-merger> /?)

# parameter to show version number
add_test(NAME feed-merger_version
         COMMAND $<TARGET_FILE:feed-merger> --version)

# redirect handling
# Feeds at heise.de are provided via "generic" URLs that are redirected
# to the current incarnation of that feed. We can use this to test the
# redirection handling of feed-merger.
add_test(NAME feed-merger_redirects
         COMMAND $<TARGET_FILE:feed-merger> "http://www.heise.de/open/news/news.rdf" "http://www.heise.de/security/news/news.rdf")
