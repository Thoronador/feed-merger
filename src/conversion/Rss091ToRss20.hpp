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

#ifndef RSS091TORSS20_HPP_INCLUDED
#define RSS091TORSS20_HPP_INCLUDED

#include "../rss0.91/Item.hpp"
#include "../rss2.0/Item.hpp"

namespace conversion
{

/** \brief converts an RSS 0.91 item to an RSS 2.0 item
 *
 * \param item091  the RSS 0.91 item
 * \return Returns a corresponding RSS2.0 item.
 */
RSS20::Item toRSS20(const RSS091::Item& item091);


} //namespace

#endif // RSS091TORSS20_HPP_INCLUDED
