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

   This program tests whether the parser can parse the simple example feed from
   the RSS 0.91 specification.
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

  if (!feed.items().empty())
  {
    std::cout << "Error: Feed " << pathToFeed << " contains some items, "
              << "although it should be empty!" << std::endl;
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
  //language
  if (feed.language() != "en")
  {
    std::cout << "Error: Unexpected value for feed language: "
              << feed.language() << "!" << std::endl;
    return 1;
  }

  const RSS091::Image expectedImage = RSS091::Image(
                    "http://www.scripting.com/gifs/tinyScriptingNews.gif", //url
                    "Scripting News", //title
                    "http://www.scripting.com/", //link
                    RSS091::Image::NoDimension, //width
                    RSS091::Image::NoDimension, //height
                    "" //description
                );

  //compare feed image
  if (feed.image() != expectedImage)
  {
    std::cout << "Parsed feed image and expected feed image do not match!"
              << std::endl;
    return 1;
  }

  //expected feed content
  const RSS091::Channel expectedFeed = RSS091::Channel(
           "Scripting News", //title
           "http://www.scripting.com/", //link
           "News and commentary for the cross-platform scripting community.", //desc.
           { }, //items
           "en", //language
           "", //copyright
           "", //managing editor
           "", //webmaster
           RSS091::Channel::NoDate, //pubDate
           RSS091::Channel::NoDate, //lastBuildDate
           "", //docs
           expectedImage //image
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
