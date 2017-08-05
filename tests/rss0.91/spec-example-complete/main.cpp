/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger test suite.
    Copyright (C) 2017  Dirk Stolle

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
#include "../../../src/rss0.91/Channel.hpp"
#include "../../../src/rss0.91/Parser.hpp"

/* Test:

   This program tests whether the parser can parse the more complete example
   feed from the RSS 0.91 specification.
*/

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
  RSS091::Channel feed = RSS091::Channel();

  if (!RSS091::Parser::fromFile(pathToFeed, feed))
  {
    std::cout << "Error: Could not parse feed " << pathToFeed << " as RSS 0.91!"
              << std::endl;
    return 1;
  }

  /* Check parsed values against values in XML file. */
  //title
  if (feed.title() != "Scripting News")
  {
    std::cout << "Error: Unexpected value for feed title: " << feed.title()
              << "!" << std::endl;
    return 1;
  }
  //link
  if (feed.link() != "http://www.scripting.com/")
  {
    std::cout << "Error: Unexpected value for feed link: " << feed.link()
              << "!" << std::endl;
    return 1;
  }
  //description
  if (feed.description() != "News and commentary from the cross-platform scripting community.")
  {
    std::cout << "Error: Unexpected value for feed description: "
              << feed.description() << "!" << std::endl;
    return 1;
  }

  //items
  const auto expectedFirstItem = RSS091::Item("stuff", "http://bar", "This is an article about some stuff");
  if (feed.items().size() != 1)
  {
    std::cout << "Error: Feed " << pathToFeed << " contains " << feed.items().size()
              << " items, although it should contain exactly one item!" << std::endl;
    return 1;
  }
  if (!(feed.items().at(0) == expectedFirstItem))
  {
    std::cout << "Error: First feed item does not match the expected item!"
              << std::endl;
    return 1;
  }

  //language
  if (feed.language() != "en-us")
  {
    std::cout << "Error: Unexpected value for feed language: "
              << feed.language() << "!" << std::endl;
    return 1;
  }

  const RSS091::Image expectedImage = RSS091::Image(
                    "http://www.scripting.com/gifs/tinyScriptingNews.gif", //url
                    "Scripting News", //title
                    "http://www.scripting.com/", //link
                    78, //width
                    40, //height
                    "What is this used for?" //description
                );

  //compare feed image
  if (feed.image() != expectedImage)
  {
    std::cout << "Parsed feed image and expected feed image do not match!"
              << std::endl;
    return 1;
  }

  //pubDate: Thu, 08 Jul 1999 07:00:00 GMT
  struct tm tempTM;
  tempTM.tm_year = 99; //1900-based
  tempTM.tm_mon = 6; //zero-based
  tempTM.tm_mday = 8; //one-based
  tempTM.tm_yday = 0;
  tempTM.tm_hour = 7;
  tempTM.tm_min = 0;
  tempTM.tm_sec = 0;
  tempTM.tm_gmtoff = 0;
  tempTM.tm_isdst = -1;
  const std::time_t expectedChannelPubDate = std::mktime(&tempTM);

  //compare publication dates
  if (feed.pubDate() != expectedChannelPubDate)
  {
    std::cout << "Parsed feed publication date and expected feed publication date do not match!"
              << std::endl;
    return 1;
  }

  //lastBuildDate: Thu, 08 Jul 1999 16:20:26 GMT
  tempTM.tm_year = 99; //1900-based
  tempTM.tm_mon = 6; //zero-based
  tempTM.tm_mday = 8; //one-based
  tempTM.tm_yday = 0;
  tempTM.tm_hour = 16;
  tempTM.tm_min = 20;
  tempTM.tm_sec = 26;
  tempTM.tm_gmtoff = 0;
  tempTM.tm_isdst = -1;
  const std::time_t expectedLastBuildDate = std::mktime(&tempTM);

  //compare build dates
  if (feed.lastBuildDate() != expectedLastBuildDate)
  {
    std::cout << "Parsed feed build date and expected feed build date do not match!"
              << std::endl;
    return 1;
  }

  const std::string expectedRating = "(PICS-1.1 \"http://www.rsac.org/ratingsv01.html\" l gen true comment \"RSACi North America Server\" for \"http://www.rsac.org\" on \"1996.04.16T08:15-0500\" r (n 0 s 0 v 0 l 0))";
  //compare build dates
  if (feed.rating() != expectedRating)
  {
    std::cout << "Parsed feed rating and expected feed rating do not match!"
              << std::endl;
    return 1;
  }

  //expected feed content
  const RSS091::Channel expectedFeed = RSS091::Channel(
           "Scripting News", //title
           "http://www.scripting.com/", //link
           "News and commentary from the cross-platform scripting community.", //desc.
           { RSS091::Item("stuff", "http://bar", "This is an article about some stuff") }, //items
           "en-us", //language
           "Copyright 1997-1999 UserLand Software, Inc.", //copyright
           "dave@userland.com (Dave Winer)", //managing editor
           "dave@userland.com (Dave Winer)", //webmaster
           expectedChannelPubDate, //pubDate
           expectedLastBuildDate, //lastBuildDate
           "http://my.userland.com/stories/storyReader$11", //docs
           expectedImage, //image
           expectedRating, //rating
           RSS091::TextInput("Search Now!", "Enter your search terms", "find", "http://my.site.com/search.cgi"), //text input
           {6, 7, 8, 9, 10, 11}, //skipHours
           { BasicRSS::Days::Sunday } //skipDays
       );

  //compare complete feed
  if (feed != expectedFeed)
  {
    std::cout << "Parsed feed and expected feed do not match!"
              << std::endl;
    return 1;
  }

  //All is well, so far.
  return 0;
}
