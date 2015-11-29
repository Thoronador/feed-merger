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

#include "Link.hpp"

namespace Atom10
{

Link::Link()
: m_href(""),
  m_rel(""),
  m_type(""),
  m_hreflang(""),
  m_title(""),
  m_length(0)
{
}

Link::Link(const std::string& href, const std::string& rel,
           const std::string& type, const std::string& hreflang,
           const std::string& title, const uint64_t length)
: m_href(href),
  m_rel(rel),
  m_type(type),
  m_hreflang(hreflang),
  m_title(title),
  m_length(0)
{
}

const std::string& Link::href() const
{
  return m_href;
}

void Link::setHref(const std::string& href)
{
  m_href = href;
}

const std::string& Link::rel() const
{
  return m_rel;
}

void Link::setRel(const std::string& rel)
{
  m_rel = rel;
}

const std::string& Link::type() const
{
  return m_type;
}

void Link::setType(const std::string& type)
{
  m_type = type;
}

const std::string& Link::hreflang() const
{
  return m_hreflang;
}

void Link::setHreflang(const std::string& hreflang)
{
  m_hreflang = hreflang;
}

const std::string& Link::title() const
{
  return m_title;
}

void Link::setTitle(const std::string& title)
{
  m_title = title;
}

uint64_t Link::length() const
{
  return m_length;
}

void Link::setLength(const uint64_t length)
{
  m_length = length;
}

bool Link::empty() const
{
  /* Only href is mandatory, so only check that. */
  return (m_href.empty());
}

bool Link::operator==(const Link& other) const
{
  return ((m_href == other.m_href) && (m_rel == other.m_rel)
       && (m_type == other.m_type) && (m_hreflang == other.m_hreflang)
       && (m_title == other.m_title) && (m_length == other.m_length));
}

} //namespace
