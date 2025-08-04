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

#include "Date.hpp"
#include <cstring>
#include "../StringFunctions.hpp"

bool rfc822DateTimeToTimeT(const std::string& rfcDate, std::time_t& output)
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

  const auto parts = splitAtSeparator(workString, ' ');

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
  const auto timeParts = splitAtSeparator(parts[3], ':');
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
  if (timeParts.size() >= 3)
  {
    if (!stringToUnsignedInt(timeParts[2], second))
      return false;
    if (second >= 60)
      return false;
  }
  else
    second = 0;

  /* zone        =  "UT"  / "GMT"                ; Universal Time
                                                 ; North American : UT
                 /  "EST" / "EDT"                ;  Eastern:  - 5/ - 4
                 /  "CST" / "CDT"                ;  Central:  - 6/ - 5
                 /  "MST" / "MDT"                ;  Mountain: - 7/ - 6
                 /  "PST" / "PDT"                ;  Pacific:  - 8/ - 7
                 /  1ALPHA                       ; Military: Z = UT;
                                                 ;  A:-1; (J not used)
                                                 ;  M:-12; N:+1; Y:+12
                 / ( ("+" / "-") 4DIGIT )        ; Local differential
                                                 ;  hours+min. (HHMM) */

  //time offset
  int offset = 0; //offset in seconds
  if (parts[4] == "GMT" || parts[4] == "UT" /* not UTC, but UT!*/)
    offset = 0;
  else if (parts[4] == "EST") offset = -5 * 60 * 60;
  else if (parts[4] == "EDT") offset = -4 * 60 * 60;
  else if (parts[4] == "CST") offset = -6 * 60 * 60;
  else if (parts[4] == "CDT") offset = -5 * 60 * 60;
  else if (parts[4] == "MST") offset = -7 * 60 * 60;
  else if (parts[4] == "MDT") offset = -6 * 60 * 60;
  else if (parts[4] == "PST") offset = -8 * 60 * 60;
  else if (parts[4] == "PDT") offset = -7 * 60 * 60;
  else if (parts[4] == "A") offset = -1 * 60 * 60;
  else if (parts[4] == "B") offset = -2 * 60 * 60;
  else if (parts[4] == "C") offset = -3 * 60 * 60;
  else if (parts[4] == "D") offset = -4 * 60 * 60;
  else if (parts[4] == "E") offset = -5 * 60 * 60;
  else if (parts[4] == "F") offset = -6 * 60 * 60;
  else if (parts[4] == "G") offset = -7 * 60 * 60;
  else if (parts[4] == "H") offset = -8 * 60 * 60;
  else if (parts[4] == "I") offset = -9 * 60 * 60;
  // J not in use
  else if (parts[4] == "K") offset = -10 * 60 * 60;
  else if (parts[4] == "L") offset = -11 * 60 * 60;
  else if (parts[4] == "M") offset = -12 * 60 * 60;
  else if (parts[4] == "N") offset = +1 * 60 * 60;
  else if (parts[4] == "O") offset = +2 * 60 * 60;
  else if (parts[4] == "P") offset = +3 * 60 * 60;
  else if (parts[4] == "Q") offset = +4 * 60 * 60;
  else if (parts[4] == "R") offset = +5 * 60 * 60;
  else if (parts[4] == "S") offset = +6 * 60 * 60;
  else if (parts[4] == "T") offset = +7 * 60 * 60;
  else if (parts[4] == "U") offset = +8 * 60 * 60;
  else if (parts[4] == "V") offset = +9 * 60 * 60;
  else if (parts[4] == "W") offset = +10 * 60 * 60;
  else if (parts[4] == "X") offset = +11 * 60 * 60;
  else if (parts[4] == "Y") offset = +12 * 60 * 60;
  else if (parts[4].size() == 5)
  {
    unsigned int offHours = 0;
    if (!stringToUnsignedInt(parts[4].substr(1,2), offHours))
      return false;
    if (offHours > 12)
      return false;
    unsigned int offMinutes = 0;
    if (!stringToUnsignedInt(parts[4].substr(3,2), offMinutes))
      return false;
    if (offMinutes > 59)
      return false;
    offset = offHours * 60 * 60 + offMinutes * 60;
    if (parts[4].at(0) == '-')
      offset = -offset;
    else if (parts[4].at(0) != '+')
      return false;
  } //else
  else
    // invalid timezone / offset specification
    return false;

  //put data into std::tm
  struct tm timeStructure;
  std::memset(&timeStructure, 0, sizeof(struct tm));

  timeStructure.tm_year = year - 1900; //years since 1900
  timeStructure.tm_mon = month - 1; //months since January
  timeStructure.tm_mday = dayOfMonth;
  timeStructure.tm_hour = hour;
  timeStructure.tm_min = minute;
  timeStructure.tm_sec = second;
  timeStructure.tm_gmtoff = offset;
  timeStructure.tm_isdst = -1; //no information on DST

  const std::time_t tt = std::mktime(&timeStructure);
  // Return value -1 means failure of mktime().
  if (tt == -1)
    return false;
  output = tt;
  return true;
}

bool timeToRFC822String(const std::time_t t, std::string& output)
{
  struct std::tm* tempTM = std::localtime(&t);
  if (nullptr == tempTM)
    return false;
  const struct std::tm savedTM(*tempTM);
  //set "C" locale to get uniform, locale-independent behaviour
  char * curLocale = std::setlocale(LC_TIME, nullptr);
  if (nullptr == curLocale)
    return false;
  const std::string previousLocale(curLocale);
  if (previousLocale != "C")
  {
    //set new "C" locale
    char * newLocale = std::setlocale(LC_TIME, "C");
    if (nullptr == newLocale)
      return false;
  } //if locale is not "C"

  char buffer[128];
  std::memset(buffer, '\0', 128);

  //format like "Mon, 02 Nov 2015 11:01:43 -0500"
  const std::size_t bytesWritten = std::strftime(buffer, 127, "%a, %d %b %Y %H:%M:%S", &savedTM);
  //set locale back
  if (previousLocale != "C")
  {
    //set old locale
    char * oldLocale = std::setlocale(LC_TIME, previousLocale.c_str());
    if (nullptr == oldLocale)
      return false;
  } //if locale was not "C"
  //Did strftime() fail?
  if (bytesWritten <= 0)
  {
    return false;
  }
  //set result
  output = std::string(buffer) + " GMT";
  return true;
}
