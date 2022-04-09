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
#include "../../../src/rss2.0/Cloud.hpp"

TEST_CASE("RSS2.0 Cloud")
{
  using namespace RSS20;

  SECTION("constructor")
  {
    SECTION("empty cloud")
    {
      Cloud cloud;

      REQUIRE( cloud.domain().empty() );
      REQUIRE( cloud.port() == 0 );
      REQUIRE( cloud.path().empty() );
      REQUIRE( cloud.registerProcedure().empty() );
      REQUIRE( cloud.protocol() == Protocol::none );
    }

    SECTION("initial values")
    {
      Cloud cloud{"www.example.com", 80, "/path/to/endpoint", "rpcProcedureName", Protocol::XmlRpc};

      REQUIRE( cloud.domain() == "www.example.com" );
      REQUIRE( cloud.port() == 80 );
      REQUIRE( cloud.path() == "/path/to/endpoint" );
      REQUIRE( cloud.registerProcedure() == "rpcProcedureName" );
      REQUIRE( cloud.protocol() == Protocol::XmlRpc );
    }
  }

  SECTION("getters and setters")
  {
    Cloud cloud;

    cloud.setDomain("rpc.example.com");
    REQUIRE( cloud.domain() == "rpc.example.com" );

    cloud.setPort(443);
    REQUIRE( cloud.port() == 443 );

    cloud.setPath("/rest");
    REQUIRE( cloud.path() == "/rest" );

    cloud.setRegisterProcedure("funName");
    REQUIRE( cloud.registerProcedure() == "funName" );

    cloud.setProtocol(Protocol::HttpPost);
    REQUIRE( cloud.protocol() == Protocol::HttpPost );
  }

  SECTION("empty")
  {
    Cloud cloud;
    REQUIRE( cloud.empty() );

    SECTION("domain")
    {
      cloud.setDomain("rpc.example.com");
      REQUIRE_FALSE( cloud.empty() );
    }

    SECTION("port")
    {
      cloud.setPort(443);
      REQUIRE_FALSE( cloud.empty() );
    }

    SECTION("path")
    {
      cloud.setPath("/empty");
      REQUIRE_FALSE( cloud.empty() );
    }

    SECTION("procedure")
    {
      cloud.setRegisterProcedure("funName");
      REQUIRE_FALSE( cloud.empty() );
    }

    SECTION("protocol")
    {
      cloud.setProtocol(Protocol::HttpPost);
      REQUIRE_FALSE( cloud.empty() );
    }
  }

  SECTION("equality")
  {
    SECTION("equal")
    {
      Cloud a;
      Cloud b;
      REQUIRE( a == b );

      a.setDomain("rpc.example.com");
      b.setDomain("rpc.example.com");
      REQUIRE( a == b );

      a.setPort(443);
      b.setPort(443);
      REQUIRE( a == b );
    }

    SECTION("not equal")
    {
      Cloud a;
      Cloud b;

      SECTION("domain mismatch")
      {
        a.setDomain("rpc.example.com");
        b.setDomain("www.example.com");

        REQUIRE_FALSE( a == b );
      }

      SECTION("port mismatch")
      {
        a.setPort(443);
        b.setPort(80);

        REQUIRE_FALSE( a == b );
      }

      SECTION("path mismatch")
      {
        a.setPath("/empty");
        b.setPath("/foo");

        REQUIRE_FALSE( a == b );
      }

      SECTION("procedure mismatch")
      {
        a.setRegisterProcedure("getStuff");
        b.setRegisterProcedure("functionName");

        REQUIRE_FALSE( a == b );
      }

      SECTION("protocol mismatch")
      {
        a.setProtocol(Protocol::Soap);
        b.setProtocol(Protocol::HttpPost);

        REQUIRE_FALSE( a == b );
      }
    }
  }
}
