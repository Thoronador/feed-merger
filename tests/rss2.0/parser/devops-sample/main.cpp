/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger test suite.
    Copyright (C) 2015  Dirk Stolle

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
  //description
  if (feed.description() != std::string("Say it with pictures. Describe your feelings about your everyday sysadmin interactions.")
                            + "\n\n"
                            + "Inspired by Infosec Reactions.")
  {
    std::cout << "Error: Unexpected value for feed description: "
              << feed.description() << "!" << std::endl;
    return 1;
  }
  //title
  if (feed.title() != "DevOps Reactions")
  {
    std::cout << "Error: Unexpected value for feed title: " << feed.title()
              << "!" << std::endl;
    return 1;
  }
  //generator
  if (feed.generator() != "Tumblr (3.0; @devopsreactions)")
  {
    std::cout << "Error: Unexpected value for feed generator: "
              << feed.generator() << "!" << std::endl;
    return 1;
  }
  //link
  if (feed.link() != "http://devopsreactions.tumblr.com/")
  {
    std::cout << "Error: Unexpected value for feed link: " << feed.link()
              << "!" << std::endl;
    return 1;
  }

  //Check number of items.
  if (feed.items().size() != 20)
  {
    std::cout << "Error: Unexpected number of items in feed: found "
              << feed.items().size() << " item(s), but 20 were expected!"
              << std::endl;
    return 1;
  }

  struct tm tempTM;
  tempTM.tm_year = 115;
  tempTM.tm_mon = 9;
  tempTM.tm_mday = 23;
  tempTM.tm_yday = 0;
  tempTM.tm_hour = 10;
  tempTM.tm_min = 00;
  tempTM.tm_sec = 21;
  tempTM.tm_gmtoff = 0;
  tempTM.tm_isdst = -1;
  //pubDate is: Fri, 23 Oct 2015 10:00:21 +0100
  //First item.
  const RSS20::Item expectedFirst = RSS20::Item(
      "Salesperson coming after you on Friday, end of month", //title
      "http://devopsreactions.tumblr.com/post/131738532813", //link
      std::string("<figure data-orig-width=\"322\" data-orig-height=\"385\" class=\"tmblr-full\">")
          + "<img data-orig-width=\"322\" data-orig-height=\"385\" src=\"http://33.media.tumblr.com/6204e2a3e75edbb21b6cbecf33f1e408/tumblr_inline_nwfyl5kHZl1raprkq_500.gif\"/>"
          + std::string("</figure><p>by @uaiHebert<br/></p>"), //desc
      "", //author
      { }, //category
      "", //comments
      RSS20::Enclosure(),
      RSS20::GUID("http://devopsreactions.tumblr.com/post/131738532813", true), //guid
      std::mktime(&tempTM), //Fri, 23 Oct 2015 10:00:21 +0100
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
