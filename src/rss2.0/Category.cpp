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

const std::string& Category::domain() const
{
  return m_domain;
}

const bool Category::empty() const
{
  //Attribute domain is optional, so we do not need to check for it.
  //However, the category itself is required for a category element.
  return m_category.empty();
}

} //namespace
