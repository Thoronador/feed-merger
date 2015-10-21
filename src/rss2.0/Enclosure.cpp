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

const uint64_t Enclosure::length() const
{
  return m_length;
}

const std::string& Enclosure::type() const
{
  return m_type;
}

} //namespace
