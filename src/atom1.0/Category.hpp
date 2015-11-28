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

#ifndef ATOM10_CATEGORY_HPP
#define ATOM10_CATEGORY_HPP

#include <string>

namespace Atom10
{

  class Category
  {
    public:
      /** \brief default constructor
       */
      Category();


      /** \brief alternative constructor with initial values
       *
       * \param term    initial value for term
       * \param scheme  initial value for scheme
       * \param label   initial value for label
       */
      Category(const std::string& term, const std::string& scheme, const std::string& label);


      /** \brief returns the category
       *
       * \return Returns the category.
       */
      const std::string& term() const;


      /** \brief sets a new term/category
       *
       * \param term  the new term/category
       */
      void setTerm(const std::string& term);


      /** \brief returns the scheme
       *
       * \return Returns the IRI that identifies categorization scheme.
       */
      const std::string& scheme() const;


      /** \brief sets a new scheme
       *
       * \param scheme  the new IRI that identifies categorization scheme
       */
      void setScheme(const std::string& scheme);


      /** \brief returns the label
       *
       * \return Returns the human-readable label for display in end-user applications.
       */
      const std::string& label() const;


      /** \brief sets a new label
       *
       * \param label  the new human-readable label for display in end-user applications
       */
      void setLabel(const std::string& label);


      /** \brief checks whether this element is empty
       *
       * \return Returns true, if this element is empty.
       * Returns false, if it contains some data.
       */
      bool empty() const;


      /** \brief equality operator for Category
       *
       * \param other  the other instance
       * \return Returns true, if both instances are equal.
       */
      bool operator==(const Category& other) const;
    private:
      std::string m_term; /**< identifies the category */
      std::string m_scheme; /**< IRI that identifies categorization scheme */
      std::string m_label; /**< human-readable label for display in end-user applications */
  }; //class

} //namespace

#endif // ATOM10_CATEGORY_HPP
