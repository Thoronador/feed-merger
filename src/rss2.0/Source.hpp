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

#ifndef RSS20_SOURCE_HPP
#define RSS20_SOURCE_HPP

#include <string>

namespace RSS20
{
  class Source
  {
    public:
      /** \brief default constructor
       *
       * \param _source text of the source element
       * \param url  the value of the URL attribute
       */
      explicit Source(const std::string& _source = "", const std::string& url = "");


      /** \brief gets the source
       *
       * \return Returns the source's name.
       */
      const std::string& get() const;


      /** \brief gets the source's URL
       *
       * \return Returns the value of the url attribute.
       */
      const std::string& url() const;


      /** \brief checks whether this element is empty
       *
       * \return Returns true, if this element is empty.
       * Returns false, if it contains some data.
       */
      bool empty() const;


      /** \brief equality operator for Source class
       *
       * \param other  another Source instance
       * \return Returns true, if this instance and other are equal.
       */
      bool operator==(const Source& other) const;
    private:
      std::string m_source; /**< source's name */
      std::string m_url; /**< value of the URL attribute */
  }; //class
} //namespace

#endif // RSS20_SOURCE_HPP
