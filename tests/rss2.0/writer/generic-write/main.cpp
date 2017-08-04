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
#include "../../../../src/rss2.0/Channel.hpp"
#include "../../../../src/rss2.0/Parser.hpp"
#include "../../../../src/rss2.0/Writer.hpp"

int main(int argc, char ** argv)
{
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

  const RSS20::Channel outputChannel = RSS20::Channel(
          "Writer test feed", //title
          "http://rss2test.example.com/path/", //link
          "Picture this!", //description
          std::vector<RSS20::Item>(1,
              RSS20::Item("Why?", //title
                          "http://rss2test.example.com/item1.html", //link
                          "A glass of wine", //description
                          "W. Riter <wr@example.com>", //author
                          { RSS20::Category("Cats", "http://cat-content.example.com/cats/") },
                          "http://rss2test.example.com/comments.php", //comments
                          RSS20::Enclosure("http://rss2test.example.com/url.txt", 5098, "text/plain"), //enclosure
                          RSS20::GUID("http://www.example.com/guid-unknown-404", false), //guid
                          std::mktime(&tempTM),
                          RSS20::Source("The Stuff's Source", "https://www.example.com/stuff.xml"))), //items
          "en-gb", //language
          "GNU FDL 1.3 for this feed", //copyright
          "W. Riter <wr@example.com>", //managing editor
          "M. Aster <ma@example.com>", //webmaster
          std::mktime(&tempTM), //pubDate
          std::mktime(&tempTM), //lastBuildDate
          { RSS20::Category("Cats & hats", "http://cat-content.example.com/") }, //category
          "feed-merger with libxml2", //generator
          "http://www.rssboard.org/rss-specification", //docs
          RSS20::Cloud("rpc.example.com", 80, "/RPC2", "myCloud.rssPleaseNotify", "xml-rpc"), //cloud
          60, //ttl
          RSS20::Image("http://rss2test.example.com/resource/image.png", //url
                       "Well-formed test feed", //title
                       "http://rss2test.example.com/image/", //link
                       81,
                       38,
                       "Funny, there is no image."), //image
          std::string("(PICS-1.1 \"http://www.gcf.org/v2.5\" by \"Jim Johnson\"")
            + std::string(" labels on \"1994.11.05T08:15-0500\" until \"1995.12.31T23:59-0000\"")
            + " for \"http://w3.org/PICS/Overview.html\" ratings (suds 0.5 density 0 color/hue 1)"
            + " for \"http://w3.org/PICS/Underview.html\" by \"Jane Johandottir\" ratings (subject 2 density 1 color/hue 1))", //rating
          RSS20::TextInput("Title for the button",
              "Your aggregator supports the textInput element. What software are you using?",
              "object_name",
              "http://www.example.com/text-collector/script.cgi"), //textInput
          { 0, 1, 8, 9, 17, 22, 23 }, //skipHours
          { BasicRSS::Days::Monday, BasicRSS::Days::Tuesday, BasicRSS::Days::Wednesday,
            BasicRSS::Days::Thursday, BasicRSS::Days::Friday, BasicRSS::Days::Saturday,
            BasicRSS::Days::Sunday } //skipDays
      );

  /* Write feed to a file. */
  const std::string fileName = "test-rss-2.xml";
  if (!RSS20::Writer::toFile(outputChannel, fileName))
  {
    std::cout << "Error: Could not write feed to file!" << std::endl;
    return 1;
  }

  /* Try to read the file with the parser and check its contents against the
     feed that was written to the disk. */
  RSS20::Channel readFeed;
  if (!RSS20::Parser::fromFile(fileName, readFeed))
  {
    std::cout << "Error: Could not read the written feed!" << std::endl;
    return 1;
  }

  if (readFeed != outputChannel)
  {
    std::cout << "Error: Original feed and the feed parsed from the written file do not match!" << std::endl;
    return 1;
  }

  //All is well, so far.
  return 0;
}
