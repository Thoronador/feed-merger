/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger.
    Copyright (C) 2015, 2017  Dirk Stolle

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

#include "TextInput.hpp"

namespace BasicRSS
{

TextInput::TextInput()
: m_title(""),
  m_description(""),
  m_name(""),
  m_link("")
{
}

TextInput::TextInput(const std::string& title, const std::string& description,
                const std::string& name, const std::string& link)
: m_title(title),
  m_description(description),
  m_name(name),
  m_link(link)
{
}

const std::string& TextInput::title() const
{
  return m_title;
}

void TextInput::setTitle(const std::string& title)
{
  m_title = title;
}

const std::string& TextInput::description() const
{
  return m_description;
}

void TextInput::setDescription(const std::string& description)
{
  m_description = description;
}

const std::string& TextInput::name() const
{
  return m_name;
}

void TextInput::setName(const std::string& name)
{
  m_name = name;
}

const std::string& TextInput::link() const
{
  return m_link;
}

void TextInput::setLink(const std::string& link)
{
  m_link = link;
}

bool TextInput::empty() const
{
  return (m_title.empty() or m_description.empty()
       or m_name.empty() or m_link.empty());
}

bool TextInput::operator==(const TextInput& other) const
{
  return ((m_title == other.m_title) and (m_description == other.m_description)
      and (m_name == other.m_name) and (m_link == other.m_link))  ;
}

} //namespace
