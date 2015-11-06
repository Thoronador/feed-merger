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
           const std::set<Category>& category, const std::string& comments,
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

const std::string& Item::author() const
{
  return m_author;
}

void Item::setAuthor(const std::string& author)
{
  m_author = author;
}

const std::set<Category>& Item::category() const
{
  return m_category;
}

void Item::setCategory(const std::set<Category>& category)
{
  m_category = category;
}

void Item::addCategory(const Category& category)
{
  m_category.insert(category);
}

const std::string& Item::comments() const
{
  return m_comments;
}

void Item::setComments(const std::string& comment)
{
  m_comments = comment;
}

const Enclosure& Item::enclosure() const
{
  return m_enclosure;
}

void Item::setEnclosure(const Enclosure& enclosure)
{
  m_enclosure = enclosure;
}

const GUID& Item::guid() const
{
  return m_guid;
}

void Item::setGUID(const GUID& guid)
{
  m_guid = guid;
}

const std::time_t Item::pubDate() const
{
  return m_pubDate;
}

void Item::setPubDate(const std::time_t& pubDate)
{
  m_pubDate = pubDate;
}

const Source& Item::source() const
{
  return m_source;
}

void Item::setSource(const Source& source)
{
  m_source = source;
}

bool Item::empty() const
{
  /* All elements of an item are optional, however at least one of title or
     description must be present. */
  return (m_title.empty() && m_description.empty());
}

bool Item::operator==(const Item& other) const
{
  return ((m_title == other.m_title) && (m_link == other.m_link)
       && (m_description == other.m_description) && (m_author == other.m_author)
       && (m_category == other.m_category) && (m_comments == other.m_comments)
       && (m_enclosure == other.m_enclosure) && (m_guid == other.m_guid)
       && (m_pubDate == other.m_pubDate) && (m_source == other.m_source));
}

bool Item::operator<(const Item& other) const
{
  return (std::difftime(other.m_pubDate, m_pubDate) > 0);
}

} //namespace
