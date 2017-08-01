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

#include "Entry.hpp"
#include <algorithm>

namespace Atom10
{

Entry::Entry()
: m_authors(std::vector<PersonConstruct>()),
  m_categories(std::vector<Category>()),
  m_contributors(std::vector<PersonConstruct>()),
  m_id(""),
  m_links(std::vector<Link>()),
  m_rights(""),
  m_summary(""),
  m_title("")
{
}

Entry::Entry(const std::vector<PersonConstruct>& authors, const std::vector<Category>& categories,
             const std::vector<PersonConstruct>& contributors, const std::string& id,
             const std::vector<Link>& links, const std::string& rights,
             const std::string& summary, const std::string& title)
: m_authors(authors),
  m_categories(categories),
  m_contributors(contributors),
  m_id(id),
  m_links(links),
  m_rights(rights),
  m_summary(summary),
  m_title(title)
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

const std::vector<Link>& Entry::links() const
{
  return m_links;
}

void Entry::setLinks(const std::vector<Link>& links)
{
  m_links = links;
}

void Entry::addLink(const Link& link)
{
  /* Link should not be empty and not be present in the vector yet. */
  if (!link.empty()
      && (std::find(m_links.begin(), m_links.end(), link) == m_links.end()))
    m_links.push_back(link);
}

const std::string& Entry::rights() const
{
  return m_rights;
}

void Entry::setRights(const std::string& rights)
{
  m_rights = rights;
}

const std::string& Entry::summary() const
{
  return m_summary;
}

void Entry::setSummary(const std::string& summary)
{
  m_summary = summary;
}

const std::string& Entry::title() const
{
  return m_title;
}

void Entry::setTitle(const std::string& title)
{
  m_title = title;
}

} //namespace
