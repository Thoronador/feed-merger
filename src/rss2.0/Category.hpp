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

#ifndef RSS20_CATEGORY_HPP
#define RSS20_CATEGORY_HPP

#include <string>

namespace RSS20
{
  /** \brief Represents an item's category element.
   */
  class Category
  {
    public:
      /** \brief Default constructor.
       *
       * \param category  the category name
       * \param domain    value of the domain attribute, optional
       */
      explicit Category(const std::string& category = "", const std::string& domain = "");


      /** \brief Gets the category's name.
       *
       * \return Returns a string representing the name.
       *         Returns an empty string, if no name is set (yet).
       */
      const std::string& get() const;


      /** \brief Sets a new category.
       *
       * \param category  the new category name
       */
      void setCategory(const std::string& category);


      /** \brief Gets the category's domain.
       *
       * \return Returns a string representing the domain.
       *         Returns an empty string, if no domain is set.
       */
      const std::string& domain() const;


      /** \brief Sets a new domain.
       *
       * \param domain  the new domain of the category
       */
      void setDomain(const std::string& domain);


      /** \brief Checks whether this element is empty.
       *
       * \return Returns true, if this element is empty.
       * Returns false, if it contains some data.
       */
      bool empty() const;


      /** \brief equality operator
       *
       * \param cat   the other category instance which will be compared to this instance
       * \return Returns true, if this category and the other category are equal.
       */
      bool operator==(const Category& cat) const;


      /** \brief "less than"-like operator
       *
       * \param cat   the other category instance which will be compared to this instance
       * \return Returns true, if this category should appear before the other
       * in a sorted set.
       */
      bool operator<(const Category& cat) const;
    private:
      std::string m_category; /**< category name */
      std::string m_domain; /**< category's domain, if any */
  }; // class
} // namespace

#endif // RSS20_CATEGORY_HPP
