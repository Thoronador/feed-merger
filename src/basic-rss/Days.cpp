/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger.
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

#include "Days.hpp"

namespace BasicRSS
{

std::string dayToString(const Days d)
{
  switch (d)
  {
    case Days::Monday:
         return "Monday";
    case Days::Tuesday:
         return "Tuesday";
    case Days::Wednesday:
         return "Wednesday";
    case Days::Thursday:
         return "Thursday";
    case Days::Friday:
         return "Friday";
    case Days::Saturday:
         return "Saturday";
    case Days::Sunday:
         return "Sunday";
  } //swi
  //should never get to this point
  throw 42;
}

} //namespace
