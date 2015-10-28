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

#ifndef RSS20_ENCLOSURE_HPP
#define RSS20_ENCLOSURE_HPP

#include <cstdint>
#include <string>

namespace RSS20
{
  class Enclosure
  {
    public:
      /** \brief default constructor
       *
       * \param url  the value of the URL attribute
       * \param length  length of the enclosure in bytes
       * \param type  media type (MIME type)
       */
      explicit Enclosure(const std::string& url = "", const uint64_t length = 0, const std::string& type = "");


      /** \brief gets the enclosure's URL
       *
       * \return Returns a string representing the enclosure's URL.
       */
      const std::string& url() const;


      /** \brief sets the URL of the enclosure
       *
       * \param url the new URL of the enclosure
       */
      void setUrl(const std::string& url);


      /** \brief gets the enclosure's length in bytes
       *
       * \return Returns a the length of the enclosure in bytes.
       */
      const uint64_t length() const;


      /** \brief sets the length of the enclosure
       *
       * \param length the new length of the enclosure
       */
      void setLength(const uint64_t length);


      /** \brief gets the enclosure's MIME type
       *
       * \return Returns a the enclosure's MIME type.
       */
      const std::string& type() const;


      /** \brief sets the MIME type of the enclosure
       *
       * \param type the new MIME type of the enclosure
       */
      void setType(const std::string& type);


      /** \brief checks whether this element is empty
       *
       * \return Returns true, if this element is empty.
       * Returns false, if it contains some data.
       */
      const bool empty() const;


      /** \brief equality operator for Enclosure
       *
       * \param other  the other instance
       * \return Returns true, if both instances are equal.
       */
      bool operator==(const Enclosure& other) const;
    private:
      std::string m_url; /**< value of the URL attribute */
      uint64_t m_length; /**< length of the media in bytes */
      std::string m_type; /**< MIME type */
  }; //class
} //namespace

#endif // RSS20_ENCLOSURE_HPP
