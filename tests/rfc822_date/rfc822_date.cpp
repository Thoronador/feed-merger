/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger's test suite.
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
#include <string>
#include <utility> //for std::pair<T1, T2>
#include <vector>
#include "../../src/rfc822/Date.hpp"

int main()
{
  std::cout << "Time conversion tests..." << std::endl;
  std::vector<std::pair<std::string, std::string> > testData;
  testData = {
      {"Mon, 18 Jan 2038 04:14:07 GMT", "2038-01-18 04:14:07"},
      {"Mon, 20 Oct 2036 20:15:00 GMT", "2036-10-20 20:15:00"},
      {"Thu, 31 Dec 2015 23:59:59 GMT", "2015-12-31 23:59:59"},
      {"Thu, 24 Dec 2015 16:30:00 GMT", "2015-12-24 16:30:00"},
      {"Wed, 11 Nov 2015 11:11:11 GMT", "2015-11-11 11:11:11"},
      {"Tue, 20 Oct 2015 23:21:19 GMT", "2015-10-20 23:21:19"},
      {"Mon, 28 Sep 2015 01:02:03 GMT", "2015-09-28 01:02:03"},
      {"Sun, 16 Aug 2015 14:15:16 GMT", "2015-08-16 14:15:16"},
      {"Sat, 25 Jul 2015 09:11:00 GMT", "2015-07-25 09:11:00"},
      {"Fri, 24 Jul 2015 11:11:11 GMT", "2015-07-24 11:11:11"},
      {"Thu, 18 Jun 2015 22:22:22 GMT", "2015-06-18 22:22:22"},
      {"Wed, 20 May 2015 10:59:59 GMT", "2015-05-20 10:59:59"},
      {"Tue, 07 Apr 2015 00:00:00 GMT", "2015-04-07 00:00:00"},
      {"Mon, 09 Mar 2015 17:01:45 GMT", "2015-03-09 17:01:45"},
      {"Sun, 22 Feb 2015 23:59:59 GMT", "2015-02-22 23:59:59"},
      {"Sat, 31 Jan 2015 00:00:00 GMT", "2015-01-31 00:00:00"},
      {"Tue, 10 Jun 2003 04:00:00 GMT", "2003-06-10 04:00:00"},
      {"Tue, 03 Jun 2003 09:39:21 GMT", "2003-06-03 09:39:21"},
      {"Fri, 30 May 2003 11:06:42 GMT", "2003-05-30 11:06:42"},
      {"Tue, 27 May 2003 08:37:32 GMT", "2003-05-27 08:37:32"},
      {"Sat, 14 Dec 1901 21:45:52 GMT", "1901-12-14 21:45:52"},
             };
  std::time_t timeOutput;

  for (auto && i : testData)
  {
    if (!rfc822DateTimeToTimeT(i.first, timeOutput))
    {
      std::cout << "Error: Could not convert " << i.first << " to std::time_t."
                << std::endl;
      return 1;
    }
    std::tm * pointer_tm = std::localtime(&timeOutput);
    char buffer[32];
    std::strftime(buffer, 32, "%Y-%m-%d %H:%M:%S", pointer_tm);
    const std::string result(buffer);
    if (result != i.second)
    {
      std::cout << "Error: String \"" << i.first << "\" should result in "
                << i.second << ", but returned value is " << result << "."
                << std::endl;
      return 1;
    }
  } //for

  //Everything is fine.
  std::cout << "Passed." << std::endl;
  return 0;
}
