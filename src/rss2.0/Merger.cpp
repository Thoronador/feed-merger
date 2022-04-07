/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger.
    Copyright (C) 2015, 2017, 2022  Dirk Stolle

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

#include "Merger.hpp"

namespace RSS20
{

bool Merger::merge(const std::vector<Channel>& feeds, Channel& result)
{
  //no feeds, no merge
  if (feeds.empty())
  {
    result = RSS20::Channel();
    return false;
  }
  //Only one feed? Trivial "merge".
  if (feeds.size() == 1)
  {
    result = feeds.at(0);
    return true;
  }

  //start with empty feed
  result = Channel();
  /* Title, link and description are required attributes. */
  result.setTitle("Merged feed (composed from " + std::to_string(feeds.size()) + " individual feeds)");
  //set placeholder for link
  result.setLink("http:///dev/null");
  //set placeholder for title
  result.setDescription("This feed was created by merging items of several feeds into one feed.");

  for (const RSS20::Channel& channel : feeds)
  {
    if (channel.items().empty())
    {
      //use data from channel instead of items (of which there are none)
      const Item channelItem = Item(channel.title(), channel.link(), channel.description(),
                        channel.managingEditor(), //"author"
                        channel.category(), "" /*comments*/, Enclosure(),
                        GUID(), channel.pubDate(), Source());
      result.addItem(channelItem);
    } //if channel has no items
    else
    {
      //add items one by one
      for (const auto & it : channel.items())
      {
        result.addItem(it);
      } //for all items in channel
    } //else
  } //for all feeds

  return true;
}

} //namespace
