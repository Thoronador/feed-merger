# feed-merger

[![GitHub CI Clang status](https://github.com/Thoronador/feed-merger/workflows/Clang/badge.svg)](https://github.com/Thoronador/feed-merger/actions)
[![GitHub CI GCC status](https://github.com/Thoronador/feed-merger/workflows/GCC/badge.svg)](https://github.com/Thoronador/feed-merger/actions)

feed-merger will be an application to merge several feeds (Atom 1.0 or RSS 2.0)
into one single feed.

## Building from source

### Prerequisites

To build the feed-merger application from source you need a C++ compiler,
CMake 3.8 or later, the cURL library and the libxml2 library.
It also helps to have Git, a distributed version control system, on your build
system to get the latest source code directly from the Git repository.

All of that can usually be installed be typing

    apt-get install cmake g++ git libcurl4-gnutls-dev libxml2-dev

or

    yum install cmake gcc-c++ git libcurl-devel libxml2-devel

into a root terminal.

### Getting the source code

Get the source directly from Git by cloning the Git repository and change to
the directory after the repository is completely cloned:

    git clone https://github.com/Thoronador/feed-merger.git ./feed-merger
    cd feed-merger

That's it, you should now have the current source code of feed-merger on your
machine.

### Build process

The build process is relatively easy, because CMake does all the preparations.
Starting in the root directory of the source, you can do the following steps:

    mkdir build
    cd build
    cmake ../
    make -j2

### Test suite

The build commands as described above also create files for a small test suite
for feed-merger. The test suite uses CTest, which usually comes with CMake.
To run the test suite, make sure you are still in the build directory that was
created during the build process and then type:

    ctest -V

If all tests succeeded, the output of the above command should end with
something like:

    100% tests passed, 0 tests failed out of 20

    Total Test time (real) =   0.64 sec

That's an indication that the basic functionality of feed-merger still works as
it was intended by the developer.


## Copyright and Licensing

Copyright 2015, 2017  Dirk Stolle

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

For the full license text, see the LICENSE file in this repository.
Alternatively, see <http://www.gnu.org/licenses/>.

## Feed format specifications

For future reference:

* Atom 1.0: RFC 4287 <http://www.ietf.org/rfc/rfc4287.txt>
* RSS 0.91: <http://www.rssboard.org/rss-0-9-1-netscape>
* RSS 1.0: <http://web.resource.org/rss/1.0/spec>
* RSS 2.0: <http://www.rssboard.org/rss-specification>

The feed-merger aims to be fully compliant to these standards / specifications.
