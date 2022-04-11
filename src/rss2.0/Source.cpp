/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger.
    Copyright (C) 2015, 2022  Dirk Stolle

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

#include "Source.hpp"

namespace RSS20
{

Source::Source(const std::string& _source, const std::string& url)
: m_source(_source),
  m_url(url)
{
}

const std::string& Source::get() const
{
  return m_source;
}

const std::string& Source::url() const
{
  return m_url;
}

bool Source::empty() const
{
  return m_source.empty() || m_url.empty();
}

bool Source::operator==(const Source& other) const
{
  return (m_source == other.m_source) && (m_url == other.m_url);
}

} // namespace
