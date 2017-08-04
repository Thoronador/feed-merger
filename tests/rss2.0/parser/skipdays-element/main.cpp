/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger test suite.
    Copyright (C) 2015, 2017  Dirk Stolle

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

#include <iostream>
#include "../../../../src/rss2.0/Parser.hpp"

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cout << "Error: Expecting exactly one argument (file name)."
              << std::endl;
    return 1;
  }

  if ((argv == nullptr) || (argv[1] == nullptr))
  {
    std::cout << "Error: Argument is null!" << std::endl;
    return 1;
  }

  const std::string pathToFeed = std::string(argv[1]);

  //initialize empty feed
  RSS20::Channel feed = RSS20::Channel();

  if (!RSS20::Parser::fromFile(pathToFeed, feed))
  {
    std::cout << "Error: Could not parse feed " << pathToFeed << " as RSS 2.0!"
              << std::endl;
    return 1;
  }

  if (feed.items().empty())
  {
    std::cout << "Error: Feed " << pathToFeed << " contains no items!"
              << std::endl;
    return 1;
  }

  struct tm tempTM;
  tempTM.tm_year = 115;
  tempTM.tm_mon = 9;
  tempTM.tm_mday = 28;
  tempTM.tm_yday = 0;
  tempTM.tm_hour = 19;
  tempTM.tm_min = 58;
  tempTM.tm_sec = 31;
  tempTM.tm_gmtoff = 0;
  tempTM.tm_isdst = -1;

  const RSS20::Channel expectedChannel = RSS20::Channel(
          "Image element test feed", //title
          "http://rss2test.example.com/image/", //link
          "Picture this!", //description
          std::vector<RSS20::Item>(1,
              RSS20::Item("Why?", //title
                          "http://rss2test.example.com/image/item1.html", //link
                          "A glass of wine", //description
                          "", //author
                          { }, //category
                          "", //comments
                          RSS20::Enclosure(), //enclosure
                          RSS20::GUID("http://www.example.com/guid-unknown-404", false), //guid
                          std::mktime(&tempTM),
                          RSS20::Source())), //items
          "", //language
          "", //copyright
          "", //managing editor
          "", //webmaster
          0, //pubDate
          0, //lastBuildDate
          { }, //category
          "", //generator
          "", //docs
          RSS20::Cloud(), //cloud
          -1, //ttl
          RSS20::Image(), //image
          "", //rating
          RSS20::TextInput(), //textInput
          {}, //skipHours
          { BasicRSS::Days::Monday, BasicRSS::Days::Tuesday, BasicRSS::Days::Wednesday,
            BasicRSS::Days::Thursday, BasicRSS::Days::Friday, BasicRSS::Days::Saturday,
            BasicRSS::Days::Sunday } //skipDays
      );


  /* Check parsed values against values in XML file. */
  //title
  if (!(feed == expectedChannel))
  {
    std::cout << "Error: Parsed feed does not match the expected feed!" << std::endl;

    if (feed.items() != expectedChannel.items())
    {
      std::cout << "Error: Unexpected value for feed items!" << std::endl;
      if (feed.items().size() != expectedChannel.items().size())
      {
        std::cout << "Expected one item, but found " << feed.items().size()
                  << " instead!" << std::endl;
      }
      return 1;
    } //if items do not match
    //skipDays
    if (feed.skipDays() != expectedChannel.skipDays())
    {
      std::cout << "Error: Channel skipDays do not match!" << std::endl;
      return 1;
    }
    return 1;
  }

  //All is well, so far.
  return 0;
}
