/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger test suite.
    Copyright (C) 2015 Thoronador

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
  RSS20::Channel feed = RSS20::Channel("", "", "", std::vector<RSS20::Item>());

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

  /* Check parsed values against values in XML file. */
  //title
  if (feed.title() != "Liftoff News")
  {
    std::cout << "Error: Unexpected value for feed title: " << feed.title()
              << "!" << std::endl;
    return 1;
  }
  //link
  if (feed.link() != "http://liftoff.msfc.nasa.gov/")
  {
    std::cout << "Error: Unexpected value for feed link: " << feed.link()
              << "!" << std::endl;
    return 1;
  }
  //description
  if (feed.description() != "Liftoff to Space Exploration.")
  {
    std::cout << "Error: Unexpected value for feed description: "
              << feed.description() << "!" << std::endl;
    return 1;
  }

  //Check number of items.
  if (feed.items().size() != 4)
  {
    std::cout << "Error: Unexpected number of items in feed: found "
              << feed.items().size() << " item(s), but four were expected!"
              << std::endl;
    return 1;
  }


  struct tm tempTM;
  tempTM.tm_year = 103;
  tempTM.tm_mon = 5;
  tempTM.tm_mday = 3;
  tempTM.tm_yday = 0;
  tempTM.tm_hour = 9;
  tempTM.tm_min = 39;
  tempTM.tm_sec = 21;
  tempTM.tm_gmtoff = 0;
  tempTM.tm_isdst = -1;

  //First item.
  const RSS20::Item expectedFirst = RSS20::Item(
      "Star City", //title
      "http://liftoff.msfc.nasa.gov/news/2003/news-starcity.asp", //link
      std::string("How do Americans get ready to work with Russians aboard the International Space Station? ")
          +"They take a crash course in culture, language and protocol at Russia's <a href=\"http://howe.iki.rssi.ru/GCTC/gctc_e.htm\">Star City</a>.", //desc
      "", //author
      { }, //category
      "", //comments
      RSS20::Enclosure(),
      RSS20::GUID("http://liftoff.msfc.nasa.gov/2003/06/03.html#item573", true), //guid
      std::mktime(&tempTM), //Tue, 03 Jun 2003 09:39:21 GMT
      RSS20::Source() //source
    );

  const RSS20::Item& parsedFirst = feed.items().at(0);

  //compare titles
  if (parsedFirst.title() != expectedFirst.title())
  {
    std::cout << "Title of first item does not match the expected value!"
              << std::endl << "Expected: " << expectedFirst.title() << std::endl
              << "Parsed: " << parsedFirst.title() << std::endl;
    return 1;
  }
  //compare link URLs
  if (parsedFirst.link() != expectedFirst.link())
  {
    std::cout << "Link URL of first item does not match the expected value!"
              << std::endl << "Expected: " << expectedFirst.link() << std::endl
              << "Parsed: " << parsedFirst.link() << std::endl;
    return 1;
  }
  //compare descriptions
  if (parsedFirst.description() != expectedFirst.description())
  {
    std::cout << "Description of first item does not match the expected value!"
              << std::endl << "Expected: " << expectedFirst.description() << std::endl
              << "Parsed: " << parsedFirst.description() << std::endl;
    return 1;
  }
  //compare GUIDs
  if (!(parsedFirst.guid() == expectedFirst.guid()))
  {
    std::cout << "GUID of first item does not match the expected value!"
              << std::endl << "Expected: " << expectedFirst.guid().get()
              << " (permalink: " << expectedFirst.guid().isPermaLink() << ")" << std::endl;
    std::cout << "Parsed: " << parsedFirst.guid().get() << " (permalink: " << parsedFirst.guid().isPermaLink() << ")" << std::endl;
    return 1;
  }
  //compare publication dates
  if (std::difftime(parsedFirst.pubDate(), expectedFirst.pubDate()) != 0)
  {
    const std::time_t expected = expectedFirst.pubDate();
    const std::time_t parsed = parsedFirst.pubDate();
    std::cout << "Publication date of first item does not match the expected value!"
              << std::endl << "Expected: " << ctime(&expected) << std::endl
              << "Expected (integer):" << static_cast<long int>(expected) << std::endl
              << "Parsed: " << ctime(&parsed) << std::endl
              << "Parsed (integer):" << static_cast<long int>(parsed) << std::endl;

    return 1;
  }
  //compare overall item
  if (!(parsedFirst == expectedFirst))
  {
    std::cout << "Parsed first feed item and expected first item do not match!"
              << std::endl;
    return 1;
  }

  //All is well, so far.
  return 0;
}
