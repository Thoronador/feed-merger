/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger.
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

#ifndef STRINGFUNCTIONS_HPP
#define STRINGFUNCTIONS_HPP

#include <string>
#include <vector>

/** \brief tries to convert a string to an unsigned integer
 *
 * \param str  the string that contains the integer
 * \param value  variable that will be used to store the integer value
 * \return Returns true, if the conversion was successful.
 *         Returns false, if an error occurred.
 */
bool stringToUnsignedInt(const std::string& str, unsigned int& value);


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

#endif // STRINGFUNCTIONS_HPP
