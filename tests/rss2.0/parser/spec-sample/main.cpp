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

  //All is well, so far.
  return 0;
}
