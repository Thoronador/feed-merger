/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger.
    Copyright (C) 2015  Dirk Stolle

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

#include "Enclosure.hpp"

namespace RSS20
{

Enclosure::Enclosure(const std::string& url, const uint64_t length, const std::string& type)
: m_url(url),
  m_length(length),
  m_type(type)
{
}

const std::string& Enclosure::url() const
{
  return m_url;
}

void Enclosure::setUrl(const std::string& url)
{
  m_url = url;
}

const uint64_t Enclosure::length() const
{
  return m_length;
}

void Enclosure::setLength(const uint64_t length)
{
  m_length = length;
}

const std::string& Enclosure::type() const
{
  return m_type;
}

void Enclosure::setType(const std::string& type)
{
  m_type = type;
}

const bool Enclosure::empty() const
{
  //All attributes are required, so all of them have to be there.
  return (m_url.empty() or (m_length == 0) or m_type.empty());
}

bool Enclosure::operator==(const Enclosure& other) const
{
  return ((m_url == other.m_url) && (m_length == other.m_length)
          && (m_type == other.m_type));
}

} //namespace
