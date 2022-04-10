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
#include "../../../src/rss2.0/Enclosure.hpp"

TEST_CASE("RSS2.0 Enclosure")
{
  using namespace RSS20;

  SECTION("constructor")
  {
    SECTION("empty enclosure")
    {
      Enclosure e;

      REQUIRE( e.url().empty() );
      REQUIRE( e.length() == 0 );
      REQUIRE( e.type().empty() );
    }

    SECTION("initial values")
    {
      Enclosure e{"https://www.example.com/foo.bar", 12480, "application/octet-stream"};

      REQUIRE( e.url() == "https://www.example.com/foo.bar" );
      REQUIRE( e.length() == 12480 );
      REQUIRE( e.type() == "application/octet-stream" );
    }
  }

  SECTION("getters and setters")
  {
    Enclosure e;

    e.setUrl("https://www.example.com/foo.ogg");
    REQUIRE( e.url() == "https://www.example.com/foo.ogg" );

    e.setLength(45678);
    REQUIRE( e.length() == 45678 );

    e.setType("audio/ogg");
    REQUIRE( e.type() == "audio/ogg" );
  }

  SECTION("empty")
  {
    Enclosure e;
    REQUIRE( e.empty() );

    SECTION("URL")
    {
      e.setUrl("https://www.example.com/foo.ogg");
      REQUIRE( e.empty() );
    }

    SECTION("length")
    {
      e.setLength(45678);
      REQUIRE( e.empty() );
    }

    SECTION("type")
    {
      e.setType("audio/ogg");
      REQUIRE( e.empty() );
    }

    SECTION("URL + length")
    {
      e.setUrl("https://www.example.com/foo.ogg");
      e.setLength(45678);
      REQUIRE( e.empty() );
    }

    SECTION("URL + type")
    {
      e.setUrl("https://www.example.com/foo.ogg");
      e.setType("audio/ogg");
      REQUIRE( e.empty() );
    }

    SECTION("length + type")
    {
      e.setLength(45678);
      e.setType("audio/ogg");
      REQUIRE( e.empty() );
    }

    SECTION("URL + length + type")
    {
      e.setUrl("https://www.example.com/foo.ogg");
      e.setLength(45678);
      e.setType("audio/ogg");
      REQUIRE_FALSE( e.empty() );
    }
  }

  SECTION("equality")
  {
    SECTION("equal")
    {
      Enclosure a;
      Enclosure b;
      REQUIRE( a == b );

      a.setUrl("https://www.example.com/foo.ogg");
      b.setUrl("https://www.example.com/foo.ogg");
      REQUIRE( a == b );

      a.setLength(98765);
      b.setLength(98765);
      REQUIRE( a == b );

      a.setType("audio/ogg");
      b.setType("audio/ogg");
      REQUIRE( a == b );
    }

    SECTION("not equal")
    {
      Enclosure a;
      Enclosure b;

      SECTION("URL mismatch")
      {
        a.setUrl("https://www.example.com/foo.ogg");
        b.setUrl("https://foo.example.com/bar.ogg");

        REQUIRE_FALSE( a == b );
      }

      SECTION("length mismatch")
      {
        a.setLength(1234);
        b.setLength(5678);

        REQUIRE_FALSE( a == b );
      }

      SECTION("type mismatch")
      {
        a.setType("audio/ogg");
        a.setType("video/ogg");

        REQUIRE_FALSE( a == b );
      }
    }
  }
}
