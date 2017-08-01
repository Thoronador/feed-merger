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

#include "Category.hpp"

namespace Atom10
{

Category::Category()
: m_term(""),
  m_scheme(""),
  m_label("")
{
}

Category::Category(const std::string& term, const std::string& scheme, const std::string& label)
: m_term(term),
  m_scheme(scheme),
  m_label(label)
{
}

const std::string& Category::term() const
{
  return m_term;
}

void Category::setTerm(const std::string& term)
{
  m_term = term;
}

const std::string& Category::scheme() const
{
  return m_scheme;
}

void Category::setScheme(const std::string& scheme)
{
  m_scheme = scheme;
}

const std::string& Category::label() const
{
  return m_label;
}

void Category::setLabel(const std::string& label)
{
  m_label = label;
}

bool Category::empty() const
{
  //Only term is mandatory, rest is optional.
  return m_term.empty();
}

bool Category::operator==(const Category& other) const
{
  return ((m_term == other.m_term) && (m_scheme == other.m_scheme)
       && (m_label == other.m_label));
}

} //namespace
