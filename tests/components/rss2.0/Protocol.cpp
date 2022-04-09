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
#include "../../../src/rss2.0/Protocol.hpp"

TEST_CASE("RSS2.0 Protocol")
{
  using namespace RSS20;

  SECTION("to_string")
  {
    REQUIRE( to_string(Protocol::XmlRpc) == "xml-rpc" );
    REQUIRE( to_string(Protocol::Soap) == "soap" );
    REQUIRE( to_string(Protocol::HttpPost) == "http-post" );
    REQUIRE( to_string(Protocol::none) == "" );
  }

  SECTION("from_string")
  {
    REQUIRE( from_string("xml-rpc") == Protocol::XmlRpc );
    REQUIRE( from_string("XML-RPC") == Protocol::XmlRpc );
    REQUIRE( from_string("xMl-RpC") == Protocol::XmlRpc );
    REQUIRE( from_string("XmL-rPc") == Protocol::XmlRpc );

    REQUIRE( from_string("soap") == Protocol::Soap );
    REQUIRE( from_string("SOAP") == Protocol::Soap );
    REQUIRE( from_string("SoAp") == Protocol::Soap );
    REQUIRE( from_string("sOaP") == Protocol::Soap );

    REQUIRE( from_string("http-post") == Protocol::HttpPost );
    REQUIRE( from_string("HTTP-POST") == Protocol::HttpPost );
    REQUIRE( from_string("HtTp-PoSt") == Protocol::HttpPost );
    REQUIRE( from_string("hTtP-pOsT") == Protocol::HttpPost );

    REQUIRE( from_string("") == Protocol::none );
    REQUIRE( from_string("foo") == Protocol::none );
    REQUIRE( from_string("whatever") == Protocol::none );
    REQUIRE( from_string("this is not a value from the spec") == Protocol::none );
  }
}
