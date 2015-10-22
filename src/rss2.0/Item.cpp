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

#include "Item.hpp"

namespace RSS20
{

Item::Item(const std::string& title, const std::string& link,
           const std::string& description, const std::string& author,
           const Category& category, const std::string& comments,
           const Enclosure& enclosure, const GUID& guid,
           const std::time_t pubDate, const Source& source)
: m_title(title),
  m_link(link),
  m_description(description),
  m_author(author),
  m_category(category),
  m_comments(comments),
  m_enclosure(enclosure),
  m_guid(guid),
  m_pubDate(pubDate),
  m_source(source)
{
}

const std::string& Item::title() const
{
  return m_title;
}

const std::string& Item::link() const
{
  return m_link;
}

const std::string& Item::description() const
{
  return m_description;
}

const std::string& Item::author() const
{
  return m_author;
}

const Category& Item::category() const
{
  return m_category;
}

const std::string& Item::comments() const
{
  return m_comments;
}

const Enclosure& Item::enclosure() const
{
  return m_enclosure;
}

const GUID& Item::guid() const
{
  return m_guid;
}

const std::time_t Item::pubDate() const
{
  return m_pubDate;
}

const Source& Item::source() const
{
  return m_source;
}

const bool Item::empty() const
{
  /* All elements of an item are optional, however at least one of title or
     description must be present. */
  return (m_title.empty() && m_description.empty());
}

} //namespace
