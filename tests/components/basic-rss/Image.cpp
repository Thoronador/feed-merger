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
#include "../../../src/basic-rss/Image.hpp"

TEST_CASE("RSS Image")
{
  using namespace BasicRSS;

  SECTION("constructor")
  {
    SECTION("empty image")
    {
      Image img;

      REQUIRE( img.url().empty() );
      REQUIRE( img.title().empty() );
      REQUIRE( img.link().empty() );
      REQUIRE_FALSE( img.width().has_value() );
      REQUIRE_FALSE( img.height().has_value() );
      REQUIRE( img.description().empty() );
    }

    SECTION("initial values")
    {
      Image img{"https://www.example.com/img.jpg", "Some title", "https://www.example.com/link/", 144, 390, "Blah blah"};

      REQUIRE( img.url() == "https://www.example.com/img.jpg" );
      REQUIRE( img.title() == "Some title" );
      REQUIRE( img.link() == "https://www.example.com/link/" );
      REQUIRE( img.width().has_value() );
      REQUIRE( img.width().value() == 144 );
      REQUIRE( img.height().has_value() );
      REQUIRE( img.height().value() == 390 );
      REQUIRE( img.description() == "Blah blah" );
    }
  }

  SECTION("getters and setters")
  {
    Image img;

    img.setUrl("https://www.example.com/img2.jpg");
    REQUIRE( img.url() == "https://www.example.com/img2.jpg" );

    img.setTitle("Foo");
    REQUIRE( img.title() == "Foo" );

    img.setLink("https://www.example.com/link2/");
    REQUIRE( img.link() == "https://www.example.com/link2/" );

    img.setWidth(123);
    REQUIRE( img.width().has_value() );
    REQUIRE( img.width().value() == 123 );

    img.setHeight(345);
    REQUIRE( img.height().has_value() );
    REQUIRE( img.height().value() == 345 );

    img.setDescription("Blah times two");
    REQUIRE( img.description() == "Blah times two" );
  }

  SECTION("empty")
  {
    Image img;
    REQUIRE( img.empty() );

    SECTION("url")
    {
      img.setUrl("https://www.example.com/img_e.jpg");
      REQUIRE_FALSE( img.empty() );
    }

    SECTION("title")
    {
      img.setTitle("Foo");
      REQUIRE_FALSE( img.empty() );
    }

    SECTION("link")
    {
      img.setLink("https://www.example.com/link2/");
      REQUIRE_FALSE( img.empty() );
    }

    SECTION("width")
    {
      img.setWidth(123);
      REQUIRE_FALSE( img.empty() );
    }

    SECTION("height")
    {
      img.setHeight(345);
      REQUIRE_FALSE( img.empty() );
    }

    SECTION("description")
    {
      img.setDescription("Some text");
      REQUIRE_FALSE( img.empty() );
    }
  }

  SECTION("equality")
  {
    SECTION("equal")
    {
      Image a;
      Image b;
      REQUIRE( a == b );
      REQUIRE_FALSE( a != b );

      a.setUrl("https://www.example.com/img.jpg");
      b.setUrl("https://www.example.com/img.jpg");
      REQUIRE( a == b );
      REQUIRE_FALSE( a != b );
    }

    SECTION("not equal")
    {
      Image a;
      Image b;

      SECTION("URL mismatch")
      {
        a.setUrl("https://www.example.com/img.jpg");
        b.setUrl("https://www.example.com/img2.jpg");

        REQUIRE_FALSE( a == b );
        REQUIRE( a != b );
      }

      SECTION("title mismatch")
      {
        a.setTitle("Foo");
        b.setTitle("Bar");

        REQUIRE_FALSE( a == b );
        REQUIRE( a != b );
      }

      SECTION("link mismatch")
      {
        a.setLink("https://www.example.com/link1/");
        b.setLink("https://www.example.com/link2/");

        REQUIRE_FALSE( a == b );
        REQUIRE( a != b );
      }

      SECTION("width mismatch")
      {
        a.setWidth(123);
        b.setWidth(144);

        REQUIRE_FALSE( a == b );
        REQUIRE( a != b );
      }

      SECTION("height mismatch")
      {
        a.setHeight(123);
        b.setHeight(31);

        REQUIRE_FALSE( a == b );
        REQUIRE( a != b );
      }

      SECTION("description mismatch")
      {
        a.setDescription("Some text");
        b.setDescription("Some other text");

        REQUIRE_FALSE( a == b );
        REQUIRE( a != b );
      }
    }
  }
}
