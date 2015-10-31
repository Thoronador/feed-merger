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
#include "../../../../src/rss2.0/Channel.hpp"
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
                          RSS20::Category(),
                          "http://rss2test.example.com/comments.php", //comments
                          RSS20::Enclosure("http://rss2test.example.com/url.txt", 5098, "text/plain"), //enclosure
                          RSS20::GUID("http://www.example.com/guid-unknown-404", false), //guid
                          std::mktime(&tempTM),
                          RSS20::Source())), //items
          "en-gb", //language
          "GNU FDL 1.3 for this feed", //copyright
          "W. Riter <wr@example.com>", //managing editor
          "M. Aster <ma@example.com>", //webmaster
          0, //pubDate
          0, //lastBuildDate
          RSS20::Category(), //category
          "feed-merger with libxml2", //generator
          "http://www.rssboard.org/rss-specification", //docs
          RSS20::Cloud(), //cloud
          -1, //ttl
          RSS20::Image(), //image
          "", //rating
          RSS20::TextInput(), //textInput
          {}, //skipHours
          { RSS20::Days::Monday, RSS20::Days::Tuesday, RSS20::Days::Wednesday,
            RSS20::Days::Thursday, RSS20::Days::Friday, RSS20::Days::Saturday,
            RSS20::Days::Sunday } //skipDays
      );

  /* Write feed to a file. */
  if (!RSS20::Writer::toFile(outputChannel, "test-rss-2.xml"))
  {
    std::cout << "Error: Could not write feed to file!" << std::endl;
    return 1;
  }

  //All is well, so far.
  return 0;
}
