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
#include "../../../src/rss2.0/Guid.hpp"

TEST_CASE("RSS 2.0 GUID")
{
  using namespace RSS20;

  SECTION("constructor")
  {
    SECTION("empty GUID")
    {
      GUID g;

      REQUIRE( g.get().empty() );
      REQUIRE_FALSE( g.isPermaLink() );
    }

    SECTION("GUID with value")
    {
      GUID g("https://www.example.com/blog/id/1234");

      REQUIRE( g.get() == "https://www.example.com/blog/id/1234" );
      REQUIRE( g.isPermaLink() );
    }

    SECTION("initial values")
    {
      GUID g{"https://www.example.com/blog/id/1234", false};

      REQUIRE( g.get() == "https://www.example.com/blog/id/1234" );
      REQUIRE_FALSE( g.isPermaLink() );
    }
  }

  SECTION("empty")
  {
    GUID g;
    REQUIRE( g.empty() );

    SECTION("URL")
    {
      g = GUID("https://www.example.com/blog/id/1234");
      REQUIRE_FALSE( g.empty() );
    }

    SECTION("permalink")
    {
      g = GUID("https://www.example.com/blog/id/1234", true);
      REQUIRE_FALSE( g.empty() );

      g = GUID("https://www.example.com/blog/id/1234", true);
      REQUIRE_FALSE( g.empty() );
    }
  }

  SECTION("equality")
  {
    SECTION("equal")
    {
      GUID a;
      GUID b;
      REQUIRE( a == b );

      a = GUID("https://www.example.com/blog/id/1234");
      b = GUID("https://www.example.com/blog/id/1234");
      REQUIRE( a == b );

      a = GUID("https://www.example.com/blog/id/1234", false);
      b = GUID("https://www.example.com/blog/id/1234", false);
      REQUIRE( a == b );

      a = GUID("https://www.example.com/blog/id/1234", true);
      b = GUID("https://www.example.com/blog/id/1234", true);
      REQUIRE( a == b );
    }

    SECTION("not equal")
    {
      GUID a;
      GUID b;

      SECTION("URL mismatch")
      {
        a = GUID("https://www.example.com/blog/id/1234");
        b = GUID("https://www.example.com/blog/id/5678");

        REQUIRE_FALSE( a == b );
      }

      SECTION("permalink mismatch")
      {
        a = GUID("https://www.example.com/blog/id/1234", false);
        b = GUID("https://www.example.com/blog/id/1234", true);

        REQUIRE_FALSE( a == b );
      }
    }
  }

  SECTION("inequality")
  {
    SECTION("equal")
    {
      GUID a;
      GUID b;
      REQUIRE( a == b );

      a = GUID("https://www.example.com/blog/id/1234");
      b = GUID("https://www.example.com/blog/id/1234");
      REQUIRE_FALSE( a != b );

      a = GUID("https://www.example.com/blog/id/1234", false);
      b = GUID("https://www.example.com/blog/id/1234", false);
      REQUIRE_FALSE( a != b );

      a = GUID("https://www.example.com/blog/id/1234", true);
      b = GUID("https://www.example.com/blog/id/1234", true);
      REQUIRE_FALSE( a != b );
    }

    SECTION("not equal")
    {
      GUID a;
      GUID b;

      SECTION("URL mismatch")
      {
        a = GUID("https://www.example.com/blog/id/1234");
        b = GUID("https://www.example.com/blog/id/5678");

        REQUIRE( a != b );
      }

      SECTION("permalink mismatch")
      {
        a = GUID("https://www.example.com/blog/id/1234", false);
        b = GUID("https://www.example.com/blog/id/1234", true);

        REQUIRE( a != b );
      }
    }
  }
}
