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

#include "Date.hpp"
#include "../StringFunctions.hpp"

bool rfc822DateTimeToTimeT(const std::string& rfcDate, time_t& output)
{
  if (rfcDate.empty())
    return false;

/*   Excerpt from RFC 822:
     =====================

     Standard for ARPA Internet Text Messages


     5.  DATE AND TIME SPECIFICATION

     5.1.  SYNTAX

     date-time   =  [ day "," ] date time        ; dd mm yy
                                                 ;  hh:mm:ss zzz

     day         =  "Mon"  / "Tue" /  "Wed"  / "Thu"
                 /  "Fri"  / "Sat" /  "Sun"

     date        =  1*2DIGIT month 2DIGIT        ; day month year
                                                 ;  e.g. 20 Jun 82

     month       =  "Jan"  /  "Feb" /  "Mar"  /  "Apr"
                 /  "May"  /  "Jun" /  "Jul"  /  "Aug"
                 /  "Sep"  /  "Oct" /  "Nov"  /  "Dec"

     time        =  hour zone                    ; ANSI and Military

     hour        =  2DIGIT ":" 2DIGIT [":" 2DIGIT]
                                                 ; 00:00:00 - 23:59:59

     zone        =  "UT"  / "GMT"                ; Universal Time
                                                 ; North American : UT
                 /  "EST" / "EDT"                ;  Eastern:  - 5/ - 4
                 /  "CST" / "CDT"                ;  Central:  - 6/ - 5
                 /  "MST" / "MDT"                ;  Mountain: - 7/ - 6
                 /  "PST" / "PDT"                ;  Pacific:  - 8/ - 7
                 /  1ALPHA                       ; Military: Z = UT;
                                                 ;  A:-1; (J not used)
                                                 ;  M:-12; N:+1; Y:+12
                 / ( ("+" / "-") 4DIGIT )        ; Local differential
                                                 ;  hours+min. (HHMM)
*/

  //Day of week is optional.
  const bool containsDayOfWeek = rfcDate.find(',') != std::string::npos;
  if (containsDayOfWeek)
  {
    const std::string dayOfWeek = rfcDate.substr(0,3);
    //check, if day is valid
    if ((dayOfWeek != "Mon") && (dayOfWeek != "Tue") && (dayOfWeek != "Wed")
        && (dayOfWeek != "Thu") && (dayOfWeek != "Fri") && (dayOfWeek != "Sat")
        && (dayOfWeek != "Sun"))
      return false;
  } //if day of week is present

  //Use copy of parameter to work with it.
  std::string workString = (containsDayOfWeek) ? rfcDate.substr(4) : rfcDate;
  //Remove leading space(s).
  while (!workString.empty() && workString.at(0) == ' ')
    workString.erase(0, 1);

  auto parts = splitAtSeparator(workString, ' ');

  if (parts.size() != 5)
    return false;

  unsigned int dayOfMonth = 0;
  if (!stringToUnsignedInt(parts[0], dayOfMonth))
    return false;
  if ((dayOfMonth <= 0) || (dayOfMonth > 31))
    return false;
  const std::string strMonth = parts[1];
  unsigned int month = 0;
  if (strMonth == "Jan")
    month = 1;
  else if (strMonth == "Feb")
    month = 2;
  else if (strMonth == "Mar")
    month = 3;
  else if (strMonth == "Apr")
    month = 4;
  else if (strMonth == "May")
    month = 5;
  else if (strMonth == "Jun")
    month = 6;
  else if (strMonth == "Jul")
    month = 7;
  else if (strMonth == "Aug")
    month = 8;
  else if (strMonth == "Sep")
    month = 9;
  else if (strMonth == "Oct")
    month = 10;
  else if (strMonth == "Nov")
    month = 11;
  else if (strMonth == "Dec")
    month = 12;
  else
    return false;

  unsigned int year = 0;
  if (!stringToUnsignedInt(parts[2], year))
    return false;
  /* Convert two digit years to four digits.
     Values greater or equal to 70 will be interpreted as 1970 - 1999.
     Values below 70 will be interpreted as 2000 - 2069.
  */
  if (year < 100)
  {
    if (year >= 70)
      year = 1900 + year;
    else
      year = 2000 + year;
  } //if only two digits (or less)

  //Parse time of the day.
  auto timeParts = splitAtSeparator(parts[3], ':');
  //At least hours and minutes are required.
  if (timeParts.size() < 2)
    return false;
  unsigned int hour = 25;
  if (!stringToUnsignedInt(timeParts[0], hour))
    return false;
  if (hour >= 24)
    return false;
  unsigned int minute = 61;
  if (!stringToUnsignedInt(timeParts[1], minute))
    return false;
  if (minute >= 60)
    return false;
  unsigned int second = 61;
  //Seconds are optional, so they may or may not be present.
  if (timeParts.size()>=3)
  {
    if (!stringToUnsignedInt(timeParts[2], second))
      return false;
    if (second >= 60)
      return false;
  }
  else
    second = 0;

  #warning Incomplete! TODO: Implement the rest.
  /* Implementation hint: Construct a std::tm object (<ctime>), then use
     std::mktime() to create an std::time_t object.
  */
  return false;
}
