/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger.
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

#include "StringFunctions.hpp"
#include <cctype>
#include <sstream>

bool stringToInt(const std::string& str, int& value)
{
  if (str.empty()) return false;
  value = 0;
  unsigned int i;
  const int cTenthLimit = std::numeric_limits<int>::max() / 10;
  const int cRealLimit = std::numeric_limits<int>::max();
  bool negative;
  if (str.at(0)=='-')
  {
    i=1;
    negative = true;
  }
  else
  {
    i=0;
    negative = false;
  }
  for ( ; i<str.size(); ++i)
  {
    if ((str.at(i)>='0') and (str.at(i)<='9'))
    {
      /* If the result of the multiplication in the next line would go out of
         the type range, then the result is not useful anyway, so quit here. */
      if (value>cTenthLimit) return false;
      value = value * 10;
      /* If the result of the addition in the next line would go out of the
         type's range, then the result is not useful anyway, so quit here. */
      if (value>cRealLimit-(str.at(i)-'0')) return false;
      value = value + (str.at(i)-'0');
    }//if
    else
    {
      //unknown or invalid character detected
      return false;
    }
  }//for
  if (negative) value = -value;
  return true;
}

std::vector<std::string> splitAtSeparator(std::string line, const char separator)
{
  std::vector<std::string> result;
  if (line.empty())
  {
    result.push_back("");
    return result;
  }
  std::string::size_type pos = line.find(separator);
  while (pos != std::string::npos)
  {
    result.push_back(line.substr(0, pos));
    line = line.substr(pos+1);
    pos = line.find(separator);
  }//while
  if (!line.empty())
  {
    result.push_back(line);
  }
  return result;
}

bool isEmptyOrWhitespace(const std::string& str)
{
  if (str.empty())
    return true;
  std::string::const_iterator iter = str.begin();
  while (iter != str.end())
  {
    const int charAsInt = static_cast<int>(*iter);
    if ((charAsInt > 127) or (!std::isspace(*iter)))
      return false;
    ++iter;
  } //while
  return true;
}
