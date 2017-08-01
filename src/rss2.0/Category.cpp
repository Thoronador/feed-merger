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

namespace RSS20
{

Category::Category(const std::string& category, const std::string& domain)
: m_category(category),
  m_domain(domain)
{
}

const std::string& Category::get() const
{
  return m_category;
}

void Category::setCategory(const std::string& category)
{
  m_category = category;
}

const std::string& Category::domain() const
{
  return m_domain;
}

void Category::setDomain(const std::string& domain)
{
  m_domain = domain;
}

const bool Category::empty() const
{
  //Attribute domain is optional, so we do not need to check for it.
  //However, the category itself is required for a category element.
  return m_category.empty();
}

bool Category::operator==(const Category& cat) const
{
  return ((m_domain == cat.m_domain) && (m_category == cat.m_category));
}

bool Category::operator<(const Category& cat) const
{
  //First compare by category. If categories are equal, then compare by domain.
  if (m_category < cat.m_category)
    return true;
  if (m_category == cat.m_category)
    return (m_domain < cat.m_domain);
  return false;
}

} //namespace
