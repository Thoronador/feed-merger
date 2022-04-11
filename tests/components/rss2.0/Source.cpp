/*
 -------------------------------------------------------------------------------
    This file is part of the test suite for feed merger.
    Copyright (C) 2022  Dirk Stolle

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 -------------------------------------------------------------------------------
*/

#include <catch.hpp>
#include "../../../src/rss2.0/Source.hpp"

TEST_CASE("RSS 2.0 Source")
{
  using namespace RSS20;

  SECTION("constructor")
  {
    SECTION("empty Source")
    {
      Source src;

      REQUIRE( src.get().empty() );
      REQUIRE( src.url().empty() );
    }

    SECTION("Source with value")
    {
      Source src("Foo's bar", "https://www.example.com/foo/bar");

      REQUIRE( src.get() == "Foo's bar" );
      REQUIRE( src.url() == "https://www.example.com/foo/bar" );
    }
  }

  SECTION("empty")
  {
    Source src;
    REQUIRE( src.empty() );

    SECTION("name")
    {
      src = Source("Foo's bar");
      REQUIRE( src.empty() );
    }

    SECTION("url")
    {
      src = Source("", "https://www.example.com/foo/bar");
      REQUIRE( src.empty() );

      src = Source("Foo's bar", "https://www.example.com/foo/bar");
      REQUIRE_FALSE( src.empty() );
    }
  }

  SECTION("equality")
  {
    SECTION("equal")
    {
      Source a;
      Source b;
      REQUIRE( a == b );

      a = Source("Foo's bar");
      b = Source("Foo's bar");
      REQUIRE( a == b );

      a = Source("Foo's bar", "https://www.example.com/foo/bar");
      b = Source("Foo's bar", "https://www.example.com/foo/bar");
      REQUIRE( a == b );

      a = Source("", "https://www.example.com/foo/bar");
      b = Source("", "https://www.example.com/foo/bar");
      REQUIRE( a == b );
    }

    SECTION("not equal")
    {
      Source a;
      Source b;

      SECTION("URL mismatch")
      {
        a = Source("Foo's bar", "https://www.example.com/foo/bar");
        b = Source("Foo's bar", "https://www.example.com/bar/foo");

        REQUIRE_FALSE( a == b );
      }

      SECTION("name mismatch")
      {
        a = Source("Foo's bar", "https://www.example.com/foo/bar");
        b = Source("Foobar", "https://www.example.com/foo/bar");

        REQUIRE_FALSE( a == b );
      }
    }
  }
}
