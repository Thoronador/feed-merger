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
                          RSS20::Enclosure("http://u.rl/file.ogg", 12345678, "audio/ogg"), //enclosure
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
          RSS20::Image() //image
      );


  /* Check parsed values against values in XML file. */
  //title
  if (!(feed == expectedChannel))
  {
    std::cout << "Error: Parsed feed does not match the expected feed!" << std::endl;

    if (feed.title() != expectedChannel.title())
    {
      std::cout << "Error: Unexpected value for feed title: " << feed.title()
                << "!" << std::endl;
      return 1;
    }
    //link
    if (feed.link() != expectedChannel.link())
    {
      std::cout << "Error: Unexpected value for feed link: " << feed.link()
                << "!" << std::endl;
      return 1;
    }
    //description
    if (feed.description() != expectedChannel.description())
    {
      std::cout << "Error: Unexpected value for feed description: "
                << feed.description() << "!" << std::endl;
      return 1;
    }
    if (feed.items() != expectedChannel.items())
    {
      std::cout << "Error: Unexpected value for feed items!" << std::endl;
      if (feed.items().size() != expectedChannel.items().size())
      {
        std::cout << "Expected one item, but found " << feed.items().size()
                  << " instead!" << std::endl;
      }
      const auto& feedFirst = feed.items().at(0);
      const auto& expectedFirst = expectedChannel.items().at(0);

      if (feedFirst.title() != expectedFirst.title())
      {
        std::cout << "Titles do not match!" << std::endl
                  << "Expected:" << expectedFirst.title() << std::endl
                  << "Parsed:  " << feedFirst.title() << std::endl;
      }
      if (feedFirst.link() != expectedFirst.link())
      {
        std::cout << "Link do not match!" << std::endl
                  << "Expected:" << expectedFirst.link() << std::endl
                  << "Parsed:  " << feedFirst.link() << std::endl;
      }
      if (feedFirst.description() != expectedFirst.description())
      {
        std::cout << "Descriptions do not match!" << std::endl
                  << "Expected:" << expectedFirst.description() << std::endl
                  << "Parsed:  " << feedFirst.description() << std::endl;
      }
      if (feedFirst.author() != expectedFirst.author())
      {
        std::cout << "Author do not match!" << std::endl
                  << "Expected:" << expectedFirst.author() << std::endl
                  << "Parsed:  " << feedFirst.author() << std::endl;
      }
      if (!(feedFirst.category() == expectedFirst.category()))
      {
        std::cout << "Categories do not match!" << std::endl;
      }
      if (feedFirst.comments() != expectedFirst.comments())
      {
        std::cout << "Comment URLs do not match!" << std::endl
                  << "Expected:" << expectedFirst.comments() << std::endl
                  << "Parsed:  " << feedFirst.comments() << std::endl;
      }
      if (!(feedFirst.enclosure() == expectedFirst.enclosure()))
      {
        std::cout << "Enclosures do not match!" << std::endl;
      }
      if (feedFirst.guid() != expectedFirst.guid())
      {
        std::cout << "GUIDs do not match!" << std::endl;
      }
      if (feedFirst.pubDate() != expectedFirst.pubDate())
      {
        std::cout << "Publication dates of first items do not match!" << std::endl
                  << "Expected date (int):" << expectedFirst.pubDate() << std::endl
                  << "Parsed date (int):  " << feedFirst.pubDate() << std::endl;
      }
      if (!(feedFirst.source() == expectedFirst.source()))
      {
        std::cout << "Sources do not match!" << std::endl;
      }
      return 1;
    } //if items do not match
    //language
    if (feed.language() != expectedChannel.language())
    {
      std::cout << "Error: Unexpected value for feed language: "
                << feed.language() << "!" << std::endl;
      return 1;
    }
    //copyright
    if (feed.copyright() != expectedChannel.copyright())
    {
      std::cout << "Error: Unexpected value for feed copyright: "
                << feed.copyright() << "!" << std::endl;
      return 1;
    }
    //managingEditor
    if (feed.managingEditor() != expectedChannel.managingEditor())
    {
      std::cout << "Error: Unexpected value for feed managingEditor: "
                << feed.managingEditor() << "!" << std::endl;
      return 1;
    }
    //webmaster
    if (feed.webMaster() != expectedChannel.webMaster())
    {
      std::cout << "Error: Unexpected value for feed webmaster: "
                << feed.webMaster() << "!" << std::endl;
      return 1;
    }
    //pubDate
    if (feed.pubDate() != expectedChannel.pubDate())
    {
      std::cout << "Publication dates of channels do not match!" << std::endl
                << "Expected date (int):" << expectedChannel.pubDate() << std::endl
                << "Parsed date (int):  " << feed.pubDate() << std::endl;
    }
    //last build date
    if (feed.lastBuildDate() != expectedChannel.lastBuildDate())
    {
      std::cout << "Build dates of channels do not match!" << std::endl
                << "Expected date (int):" << expectedChannel.lastBuildDate() << std::endl
                << "Parsed date (int):  " << feed.lastBuildDate() << std::endl;
    }
    //Category
    if (!(feed.category() == expectedChannel.category()))
    {
      std::cout << "Error: Channel categories do not match!" << std::endl;
      return 1;
    }
    //generator
    if (feed.generator() != expectedChannel.generator())
    {
      std::cout << "Error: Unexpected value for feed generator: "
                << feed.generator() << "!" << std::endl;
      return 1;
    }
    //docs
    if (feed.docs() != expectedChannel.docs())
    {
      std::cout << "Error: Unexpected value for feed docs: "
                << feed.docs() << "!" << std::endl;
      return 1;
    }
    //ttl
    if (feed.ttl() != expectedChannel.ttl())
    {
      std::cout << "Error: Unexpected value for feed ttl: "
                << feed.ttl() << "!" << std::endl;
      return 1;
    }
    //image
    if (!(feed.image() == expectedChannel.image()))
    {
      std::cout << "Error: Channel images do not match!" << std::endl;
      return 1;
    }
    return 1;
  }

  //All is well, so far.
  return 0;
}
