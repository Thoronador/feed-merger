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

#ifndef RFC822_DATE_HPP
#define RFC822_DATE_HPP

#include <ctime>
#include <string>

/** \brief converts a string that follows RFC 822 date format to a time_t value
 *
 * \param rfcDate  a string containing the date, e.g. "Sun, 19 May 2002 17:21:47 GMT"
 * \param output   time_t variable that will be used to store the resulting date
 * \return Returns true, if the date could be converted properly.
 *         Returns false, if an error occurred. The content of @arg output is
 *         undefined in such a case.
 */
bool rfc822DateTimeToTimeT(const std::string& rfcDate, std::time_t& output);


/** \brief converts the given time_t value to a RFC 822 conforming date/time string
 *
 * \param t  time_t variable
 * \param output  variable that is used to return the string representation of the given time
 * \return Returns true, if conversion was successful. Returns false otherwise.
 */
bool timeToRFC822String(const std::time_t t, std::string& output);

#endif // RFC822_DATE_HPP
