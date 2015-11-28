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

#ifndef ATOM10_PERSONCONSTRUCT_HPP
#define ATOM10_PERSONCONSTRUCT_HPP

#include <string>

namespace Atom10
{
  /** \brief class that represents an Atom 1.0 Person Construct
   *
   *  as described in chapter 3.2 of RFC 4287.
   */
  class PersonConstruct
  {
    public:
      /** \brief default constructor
       */
      PersonConstruct();


      /** \brief returns the person's name
       *
       * \return Returns the name of the person.
       */
      const std::string& name() const;


      /** \brief sets a new name
       *
       * \param name  the new name of the person
       */
      void setName(const std::string& name);


      /** \brief returns the person's URI
       *
       * \return Returns the URI related to the person, if any.
       */
      const std::string& uri() const;


      /** \brief sets a new URI
       *
       * \param uri  the new URI related to the person
       */
      void setUri(const std::string& uri);


      /** \brief returns the person's e-mail address
       *
       * \return Returns the e-mail address of the person, if any.
       */
      const std::string& email() const;


      /** \brief sets a new e-mail address of the person
       *
       * \param email  the new e-mail address of the person
       */
      void setEmail(const std::string& email);


      /** \brief checks whether this element is empty
       *
       * \return Returns true, if this element is empty.
       * Returns false, if it contains some data.
       */
      bool empty() const;


      /** \brief equality operator for PersonConstruct
       *
       * \param other  the other instance
       * \return Returns true, if both instances are equal.
       */
      bool operator==(const PersonConstruct& other) const;
    private:
      std::string m_name; /**< name of the person, mandatory */
      std::string m_uri; /**< URI associated with the person, optional */
      std::string m_email; /**< e-mail address of the person, optional */
  }; //class

} //namespace

#endif // ATOM10_PERSONCONSTRUCT_HPP
