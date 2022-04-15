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
#include "../../../src/basic-rss/Days.hpp"

TEST_CASE("RSS Days")
{
  using namespace BasicRSS;

  SECTION("dayToString")
  {
    SECTION("normal values")
    {
      REQUIRE( dayToString(Days::Monday) == "Monday" );
      REQUIRE( dayToString(Days::Tuesday) == "Tuesday" );
      REQUIRE( dayToString(Days::Wednesday) == "Wednesday" );
      REQUIRE( dayToString(Days::Thursday) == "Thursday" );
      REQUIRE( dayToString(Days::Friday) == "Friday" );
      REQUIRE( dayToString(Days::Saturday) == "Saturday" );
      REQUIRE( dayToString(Days::Sunday) == "Sunday" );
    }

    SECTION("invalid value")
    {
      BasicRSS::Days d = static_cast<BasicRSS::Days>(15);

      REQUIRE_THROWS( dayToString(d) );
    }
  }
}
