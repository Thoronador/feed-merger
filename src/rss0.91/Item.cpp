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

#include "Item.hpp"

namespace RSS091
{

Item::Item(const std::string& title, const std::string& link,
           const std::string& description)
: m_title(title),
  m_link(link),
  m_description(description)
{
}

const std::string& Item::title() const
{
  return m_title;
}

void Item::setTitle(const std::string& title)
{
  m_title = title;
}

const std::string& Item::link() const
{
  return m_link;
}

void Item::setLink(const std::string& link)
{
  m_link = link;
}

const std::string& Item::description() const
{
  return m_description;
}

void Item::setDescription(const std::string& description)
{
  m_description = description;
}

bool Item::empty() const
{
  /* Elements title and link are required, description is optional. */
  return (m_title.empty() || m_link.empty());
}

bool Item::operator==(const Item& other) const
{
  return ((m_title == other.m_title) && (m_link == other.m_link)
       && (m_description == other.m_description));
}

} //namespace
