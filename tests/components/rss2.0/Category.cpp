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
#include "../../../src/rss2.0/Category.hpp"

TEST_CASE("RSS2.0 Category")
{
  using namespace RSS20;

  SECTION("constructor")
  {
    SECTION("empty category")
    {
      Category cat;

      REQUIRE( cat.domain().empty() );
      REQUIRE( cat.get().empty() );
    }

    SECTION("category name only")
    {
      Category cat{"foobar"};

      REQUIRE( cat.domain().empty() );
      REQUIRE( cat.get() == "foobar" );
    }

    SECTION("category with domain")
    {
      Category cat{"foobar", "https://www.example.com/"};

      REQUIRE( cat.domain() == "https://www.example.com/" );
      REQUIRE( cat.get() == "foobar" );
    }
  }

  SECTION("getters and setters")
  {
    Category cat;

    cat.setCategory("blubb");
    REQUIRE( cat.get() == "blubb" );

    cat.setDomain("https://www.example.com/set");
    REQUIRE( cat.domain() == "https://www.example.com/set" );
  }

  SECTION("empty")
  {
    Category cat;
    REQUIRE( cat.empty() );

    cat.setCategory("test");
    REQUIRE_FALSE( cat.empty() );

    cat.setDomain("https://www.example.com/");
    REQUIRE_FALSE( cat.empty() );

    // Category counts as empty, if no name is set, even when domain is present,
    // because the specification requires at least a name. Domain is optional.
    cat.setCategory("");
    REQUIRE( cat.empty() );
  }

  SECTION("equality")
  {
    SECTION("equal")
    {
      Category a;
      Category b;
      REQUIRE( a == b );

      a.setCategory("foo");
      b.setCategory("foo");
      REQUIRE( a == b );

      a.setDomain("https://www.example.com/");
      b.setDomain("https://www.example.com/");
      REQUIRE( a == b );
    }

    SECTION("not equal")
    {
      Category a;
      Category b;

      SECTION("category mismatch")
      {
        a.setCategory("foo");
        b.setCategory("bar");

        REQUIRE_FALSE( a == b );
      }

      SECTION("domain mismatch")
      {
        a.setDomain("https://www.example.com/");
        b.setDomain("https://www.foo.com/");

        REQUIRE_FALSE( a == b );
      }
    }
  }

  SECTION("less than operator")
  {
    Category a;
    Category b;

    SECTION("less")
    {
      a.setCategory("foo");
      b.setCategory("test");

      REQUIRE( a < b );

      a = Category{"foo", "https://www.example.com/" };
      b = Category{"foo", "https://www.example.com/foo" };

      REQUIRE( a < b );
    }

    SECTION("equal")
    {
      REQUIRE_FALSE( a < b );

      a = Category{"foo"};
      b = Category{"foo"};
      REQUIRE_FALSE( a < b );

      a = Category{"foo", "https://www.example.com/" };
      b = Category{"foo", "https://www.example.com/" };
      REQUIRE_FALSE( a < b );
    }

    SECTION("greater")
    {
      a = Category{"foo"};
      b = Category{"bar"};
      REQUIRE_FALSE( a < b );

      a = Category{"foo", "https://www.example.com/blurb" };
      b = Category{"foo", "https://www.example.com/" };
      REQUIRE_FALSE( a < b );
    }
  }
}
