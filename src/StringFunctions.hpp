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

#ifndef STRINGFUNCTIONS_HPP
#define STRINGFUNCTIONS_HPP

#include <limits>
#include <string>
#include <type_traits>
#include <vector>

/** \brief tries to convert a string to an unsigned integer
 *
 * \param str  the string that contains the integer
 * \param value  variable that will be used to store the integer value
 * \return Returns true, if the conversion was successful.
 *         Returns false, if an error occurred.
 */
template<typename uintT>
bool stringToUnsignedInt(const std::string& str, uintT& value)
{
  static_assert(std::is_integral<uintT>::value, "uintT must be an integral type!");
  static_assert(std::is_unsigned<uintT>::value, "uintT must be an unsigned type!");
  if (str.empty()) return false;
  value = 0;
  const uintT cTenthLimit = std::numeric_limits<uintT>::max() / 10;
  const uintT cRealLimit = std::numeric_limits<uintT>::max();
  std::string::size_type i = 0;
  for ( ; i < str.size(); ++i)
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
  return true;
}


/** \brief tries to convert the string into a signed int
 *
 * \param str    the string that contains the number
 * \param value  the signed int that will be used to store the result
 * \return Returns true on success, false on failure.
 * \remarks If false is returned, the value of parameter value is undefined.
 */
bool stringToInt(const std::string& str, int& value);


/** \brief splits the given string into pieces, treating a given character
 * as the separator for values, and returns the pieces as a vector
 *
 * \param line  string containing the separated values
 * \param separator  character that serves as separator between elements
 */
std::vector<std::string> splitAtSeparator(std::string line, const char separator);


/** \brief checks whether a string is empty or consists only of whitespace characters
 *
 * \param str   the string that shall be checked
 * \return Returns true, if the string is empty or contains only whitespace characters.
 */
bool isEmptyOrWhitespace(const std::string& str);

/* Returns string representation of integer 'value' */
std::string intToString(const int value);
std::string uintToString(const unsigned int value);

#endif // STRINGFUNCTIONS_HPP
