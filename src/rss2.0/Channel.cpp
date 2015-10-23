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

#include "Channel.hpp"

namespace RSS20
{

Channel::Channel(const std::string& title, const std::string& link,
              const std::string& description, const std::vector<Item>& items)
: m_title(title),
  m_link(link),
  m_description(description),
  m_items(items)
{
}

const std::string& Channel::title() const
{
  return m_title;
}

void Channel::setTitle(const std::string& title)
{
  m_title = title;
}

const std::string& Channel::link() const
{
  return m_link;
}

void Channel::setLink(const std::string& link)
{
  m_link = link;
}

const std::string& Channel::description() const
{
  return m_description;
}

void Channel::setDescription(const std::string& description)
{
  m_description = description;
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
  return ((m_title == other.m_title) && (m_link == other.m_link)
      && (m_description == other.m_description) && (m_items == other.m_items));
}

} //namespace
