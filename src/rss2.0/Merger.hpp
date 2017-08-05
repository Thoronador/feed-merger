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

#ifndef RSS20_MERGER_HPP
#define RSS20_MERGER_HPP

#include "Channel.hpp"

namespace RSS20
{
  /** \brief merges RSS 2.0 feeds
   */
  class Merger
  {
    public:
      /** \brief merges multiple RSS 2.0 feeds into one feed
       *
       * \param feeds  list of feeds that shall be merged
       * \param result resulting feed containing all merged data
       * \return Returns true, if the merge was successful.
       *         Returns false otherwise.
       */
      static bool merge(const std::vector<Channel>& feeds, Channel& result);
  }; //class

} //namespace

#endif // RSS20_MERGER_HPP
