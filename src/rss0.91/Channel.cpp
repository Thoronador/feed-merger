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

#include "Channel.hpp"

namespace RSS091
{

Channel::Channel()
: BasicRSS::Channel(),
  m_items(std::vector<Item>())
{
}

Channel::Channel(const std::string& title, const std::string& link,
              const std::string& description, const std::vector<Item>& items,
              const std::string& language, const std::string& copyright,
              const std::string& managingEditor, const std::string& webMaster,
              const std::time_t pubDate, const std::time_t lastBuildDate,
              const std::string& docs, const Image& image,
              const std::string& rating, const TextInput& textInput,
              const std::set<unsigned int>& skipHours,
              const std::set<BasicRSS::Days>& skipDays)
: BasicRSS::Channel(title, link, description, language, copyright,
                    managingEditor, webMaster, pubDate, lastBuildDate, docs,
                    image, rating, textInput, skipHours, skipDays),
  m_items(items)
{
}

const std::vector<Item>& Channel::items() const
{
  return m_items;
}

void Channel::addItem(const Item& item)
{
  if (!item.empty())
    m_items.push_back(item);
}

bool Channel::operator==(const Channel& other) const
{
  return (BasicRSS::Channel::operator==(other) && (m_items == other.m_items));
}

bool Channel::operator!=(const Channel& other) const
{
  /* Inequality operator is the negation of the equality operator. */
  return (!(*this == other));
}

} //namespace
