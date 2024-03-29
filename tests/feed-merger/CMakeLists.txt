# We might support earlier versions, too, but try to use a recent one.
cmake_minimum_required (VERSION 3.8)

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
# Some feeds might be provided via "generic" URLs that are redirected
# to the current incarnation of that feed. We can use httpbin's redirect to
# test the redirection handling of feed-merger.
add_test(NAME feed-merger_redirects
         COMMAND $<TARGET_FILE:feed-merger> "https://httpbin.org/redirect-to?url=http%3A%2F%2Fdevopsreactions.tumblr.com%2Frss" "https://httpbin.org/redirect-to?url=http%3A%2F%2Fsecurityreactions.tumblr.com%2Frss")
