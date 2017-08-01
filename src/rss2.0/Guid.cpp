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

#include "Guid.hpp"

namespace RSS20
{

GUID::GUID(const std::string& guid, const bool isPermanent)
: m_guid(guid), m_isPermaLink(isPermanent)
{ }

const std::string& GUID::get() const
{
  return m_guid;
}

bool GUID::isPermaLink() const
{
  return m_isPermaLink && !m_guid.empty();
}

bool GUID::empty() const
{
  return m_guid.empty();
}

bool GUID::operator==(const GUID& other) const
{
  return ((m_guid == other.m_guid) && (m_isPermaLink == other.m_isPermaLink));
}

bool GUID::operator!=(const GUID& other) const
{
  return ((m_guid != other.m_guid) || (m_isPermaLink != other.m_isPermaLink));
}

} //namespace
