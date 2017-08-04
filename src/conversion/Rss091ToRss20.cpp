/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger.
    Copyright (C) 2017  Dirk Stolle

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

#include "Rss091ToRss20.hpp"
#include <ctime>
#include "../rss2.0/Enclosure.hpp"
#include "../rss2.0/Guid.hpp"
#include "../rss2.0/Source.hpp"

namespace conversion
{

RSS20::Item toRSS20(const RSS091::Item& item091)
{
  return RSS20::Item(item091.title(), item091.link(), item091.description(),
                     "" /*author */, { } /* categories */, "" /* comments */,
                     RSS20::Enclosure(), RSS20::GUID(),
                     static_cast<std::time_t>(0)/* date */, RSS20::Source());
}

} //namespace
