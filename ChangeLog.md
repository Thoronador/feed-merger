# ChangeLog for feed-merger

## version 0.08 (2022-04-11)

HTTPS connections will now try to use TLS v1.2 or newer by default, if your
system uses cURL 7.54.0 or newer. For older cURL versions, the minimum TLS
version is 1.0 as it was before. However, even on older cURL versions that does
not prevent feed-merger from using newer TLS versions (e. g. v1.2 or v1.3) as
long as the SSL library supports newer TLS versions.

## version 0.07 (2017-08-05)
  - better merge handling for RSS 2.0 feeds without items
  - adjust sort order of items in merged feed

## Version 0.06 (2015-11-06)
  - RSS 2.0 feeds with multiple categories per channel and/or per item can now
    be parsed properly.
  - Parser and Writer should now be fully compliant with RSS 2.0 specification.

## Version 0.05 (2015-11-06)
  - first version that writes the merged feeds to a file

## Version 0.04 (2015-10-31)
  - parsing of all default RSS 2.0 feed elements implemented

## Version 0.03 (2015-10-25)
  - enable feed-merger to handle redirects gracefully

## Version 0.02 (2015-10-25)
  - first version that actually fetches the feeds

## Version 0.01 (2015-10-25)
  - very simple (and very incomplete) first version
