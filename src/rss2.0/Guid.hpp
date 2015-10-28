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

#ifndef RSS20_GUID_HPP
#define RSS20_GUID_HPP

#include <string>

namespace RSS20
{
  /** \brief class to keep GUID information of an RSS 2.0 feed item
   */
  class GUID
  {
    public:
      /** default constructor */
      explicit GUID(const std::string& guid = "", const bool isPermanent = true);


      /** \brief gets the GUID's value
       *
       * \return Returns a string representing the GUID's value.
       */
      const std::string& get() const;


      /** \brief check whether the GUID is a permanent link
       *
       * \return Returns true, if the GUID is a permanent link.
       */
      bool isPermaLink() const;


      /** \brief checks whether this element is empty
       *
       * \return Returns true, if this element is empty.
       * Returns false, if it contains some data.
       */
      bool empty() const;


      /** \brief equality operator
       *
       * \param other  the other instance
       * \return Returns true, if this instance and other are equal.
       */
      bool operator==(const GUID& other) const;


      /** \brief inequality operator
       *
       * \param other  the other instance
       * \return Returns true, if this instance and other are NOT equal.
       */
      bool operator!=(const GUID& other) const;
    private:
      std::string m_guid; /**< the GUID's value */
      bool m_isPermaLink; /**< whether the GUID is a permalink or not */
  }; //class GUID
} //namespace

#endif // RSS20_GUID_HPP
