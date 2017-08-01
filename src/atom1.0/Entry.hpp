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

#ifndef ATOM10_ENTRY_HPP
#define ATOM10_ENTRY_HPP

#include <string>
#include <vector>
#include "Category.hpp"
#include "Link.hpp"
#include "PersonConstruct.hpp"

namespace Atom10
{
  /*

  atomEntry =
      element atom:entry {
         atomCommonAttributes,
         (atomAuthor*
          & atomCategory*
          & atomContent?
          & atomContributor*
          & atomId
          & atomLink*
          & atomPublished?
          & atomRights?
          & atomSource?
          & atomSummary?
          & atomTitle
          & atomUpdated
          & extensionElement*)
      }

  */
  class Entry
  {
    public:
      /** \brief default constructor
       */
      Entry();


      /** \brief alternative constructor with initial values
       *
       * \param authors       list of authors
       * \param categories    initial list of categories
       * \param contributors  list of contributors
       * \param id            the entry's ID
       * \param link          the links for the entry
       * \param rights        rights held in and over an entry or feed
       * \param summary       short summary of the entry
       * \param title         human-readable title for the entry
       */
      Entry(const std::vector<PersonConstruct>& authors, const std::vector<Category>& categories,
            const std::vector<PersonConstruct>& contributors, const std::string& id,
            const std::vector<Link>& links, const std::string& rights,
            const std::string& summary, const std::string& title);


      /** \brief returns the author(s)
       *
       * \return Returns a vector of authors.
       */
      const std::vector<PersonConstruct>& authors() const;


      /** \brief sets the authors of the entry
       *
       * \param authors   the new vector of authors
       */
      void setAuthors(const std::vector<PersonConstruct>& authors);


      /** \brief adds a new author to the entry's authors
       *
       * \param author  the additional author
       */
      void addAuthor(const PersonConstruct& author);


      /** \brief returns the categories of the entry
       *
       * \return Returns a vector of categories.
       */
      const std::vector<Category>& categories() const;


      /** \brief sets the categories of the entry
       *
       * \param categories   the new vector of categories
       */
      void setCategories(const std::vector<Category>& categories);


      /** \brief adds a new category to the entry's categories
       *
       * \param category  the additional category
       */
      void addCategory(const Category& category);


      #warning TODO: content element!



      /** \brief returns the contributor(s)
       *
       * \return Returns a vector of contributors.
       */
      const std::vector<PersonConstruct>& contributors() const;


      /** \brief sets the contributors of the entry
       *
       * \param contributors   the new vector of contributors
       */
      void setContributors(const std::vector<PersonConstruct>& contributors);


      /** \brief adds a new contributor to the entry's contributors
       *
       * \param contributor  the additional contributor
       */
      void addContributor(const PersonConstruct& contributor);


      /** \brief returns the entry's id
       *
       * \return Returns the id.
       */
      const std::string& id() const;


      /** \brief sets the id of the entry
       *
       * \param id   the new id of the entry
       */
      void setId(const std::string& id);


      /** \brief returns the link(s)
       *
       * \return Returns a vector of links.
       */
      const std::vector<Link>& links() const;


      /** \brief sets the links of the entry
       *
       * \param links   the new vector of links
       */
      void setLinks(const std::vector<Link>& links);


      /** \brief adds a new link to the entry's links
       *
       * \param link  the additional link
       */
      void addLink(const Link& link);

      #warning TODO!


      /** \brief returns the entry's copyright information
       *
       * \return Returns the copyright information.
       */
      const std::string& rights() const;


      /** \brief sets the entry's copyright information
       *
       * \param rights   the new copyright information of the entry
       */
      void setRights(const std::string& rights);

      #warning TODO


      /** \brief returns the entry's summary
       *
       * \return Returns the summary.
       */
      const std::string& summary() const;


      /** \brief sets the summary of the entry
       *
       * \param summary   the new summary of the entry
       */
      void setSummary(const std::string& summary);


      /** \brief returns the entry's title
       *
       * \return Returns the title.
       */
      const std::string& title() const;


      /** \brief sets the title of the entry
       *
       * \param title   the new title of the entry
       */
      void setTitle(const std::string& title);


      #warning TODO!
    private:
      std::vector<PersonConstruct> m_authors; /**< vector of authors */
      std::vector<Category> m_categories; /**< vector of categories */
      #warning TODO: content element!
      std::vector<PersonConstruct> m_contributors; /**< vector of contributors */
      std::string m_id; /**< id element */
      std::vector<Link> m_links; /**< vector of links */
      #warning TODO!
      std::string m_rights; /**< info about rights held in and over an entry */
      #warning TODO!
      std::string m_summary; /**< short summary, abstract or excerpt of the entry */
      std::string m_title; /**< human-readable title for the entry */
      #warning TODO!
  }; //class
} //namespace

#endif // ATOM10_ENTRY_HPP
