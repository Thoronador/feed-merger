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

#ifndef BASIC_RSS_DAYS_HPP
#define BASIC_RSS_DAYS_HPP

#include <string>

namespace BasicRSS
{
  /** enumeration type for days of the week */
  enum class Days { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};


  /** \brief Returns the name of the day as string.
   *
   * \param d  the day
   * \param
   * \return Returns a string like "Monday" etc., suitable for use in RSS 0.91
   * and RSS 2.0 <skipDays>'s <day> sub-elements.
   */
  std::string dayToString(const Days d);
} // namespace

#endif // BASIC_RSS_DAYS_HPP
