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

#include "Entry.hpp"
#include <algorithm>

namespace Atom10
{

Entry::Entry()
: m_authors(std::vector<PersonConstruct>()),
  m_categories(std::vector<Category>()),
  m_contributors(std::vector<PersonConstruct>()),
  m_id("")
{
}

const std::vector<PersonConstruct>& Entry::authors() const
{
  return m_authors;
}

void Entry::setAuthors(const std::vector<PersonConstruct>& authors)
{
  m_authors = authors;
}

void Entry::addAuthor(const PersonConstruct& author)
{
  /* Author should not be empty and not be present in the vector yet. */
  if (!author.empty()
      && (std::find(m_authors.begin(), m_authors.end(), author) == m_authors.end()))
    m_authors.push_back(author);
}

const std::vector<Category>& Entry::categories() const
{
  return m_categories;
}

void Entry::setCategories(const std::vector<Category>& categories)
{
  m_categories = categories;
}

void Entry::addCategory(const Category& category)
{
  /* Category should not be empty and not be present in the vector yet. */
  if (!category.empty()
      && (std::find(m_categories.begin(), m_categories.end(), category) == m_categories.end()))
    m_categories.push_back(category);
}

const std::vector<PersonConstruct>& Entry::contributors() const
{
  return m_contributors;
}

void Entry::setContributors(const std::vector<PersonConstruct>& contributors)
{
  m_contributors = contributors;
}

void Entry::addContributor(const PersonConstruct& contributor)
{
  /* Contributor should not be empty and not be present in the vector yet. */
  if (!contributor.empty()
      && (std::find(m_contributors.begin(), m_contributors.end(), contributor) == m_contributors.end()))
    m_contributors.push_back(contributor);
}

const std::string& Entry::id() const
{
  return m_id;
}

void Entry::setId(const std::string& id)
{
  m_id = id;
}

} //namespace
