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

#include "PersonConstruct.hpp"

namespace Atom10
{

PersonConstruct::PersonConstruct()
: m_name(""),
  m_uri(""),
  m_email("")
{
}

const std::string& PersonConstruct::name() const
{
  return m_name;
}

void PersonConstruct::setName(const std::string& name)
{
  m_name = name;
}

const std::string& PersonConstruct::uri() const
{
  return m_uri;
}

void PersonConstruct::setUri(const std::string& uri)
{
  m_uri = uri;
}

const std::string& PersonConstruct::email() const
{
  return m_email;
}

void PersonConstruct::setEmail(const std::string& email)
{
  m_email = email;
}

bool PersonConstruct::empty() const
{
  // Only name is mandatory, so we only check for that element's value.
  return m_name.empty();
}

bool PersonConstruct::operator==(const PersonConstruct& other) const
{
  return ((m_name == other.m_name) && (m_uri == other.m_uri)
       && (m_email == other.m_email));
}

} //namespace
