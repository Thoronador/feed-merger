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

#ifndef ATOM10_LINK_HPP
#define ATOM10_LINK_HPP

#include <cstdint>
#include <string>

namespace Atom10
{

  class Link
  {
    public:
      /** \brief default constructor */
      Link();


      /** \brief alternative constructor with initial values
       *
       * \param href      the link's IRI
       * \param rel       link relation type
       * \param type      media type
       * \param hreflang  language of the resource
       * \param title     human-readable title
       * \param length    length of the linked content in octets
       */
      Link(const std::string& href, const std::string& rel,
           const std::string& type, const std::string& hreflang,
           const std::string& title, const uint64_t length);


      /** \brief get the link's IRI
       *
       * \return Returns the link's IRI.
       */
      const std::string& href() const;


      /** \brief sets the link's IRI
       *
       * \param href  the new IRI
       */
      void setHref(const std::string& href);


      /** \brief get the link's relation type
       *
       * \return Returns the link's relation type.
       */
      const std::string& rel() const;


      /** \brief sets the link's relation type
       *
       * \param rel  the new relation type
       */
      void setRel(const std::string& rel);


      /** \brief get the media type
       *
       * \return Returns the link's media type.
       */
      const std::string& type() const;


      /** \brief sets the link's media type
       *
       * \param type  the new media type
       */
      void setType(const std::string& type);


      /** \brief get the linked resource's language
       *
       * \return Returns the linked resource's language.
       */
      const std::string& hreflang() const;


      /** \brief sets the linked resource's language
       *
       * \param hreflang  the new language
       */
      void setHreflang(const std::string& hreflang);


      /** \brief get the link's title
       *
       * \return Returns the link's title.
       */
      const std::string& title() const;


      /** \brief sets the link's title
       *
       * \param title  the new title
       */
      void setTitle(const std::string& title);


      /** \brief get the linked resource's length in bytes/octets
       *
       * \return Returns the linked resource's length.
       */
      uint64_t length() const;


      /** \brief sets the linked resource's length
       *
       * \param length  the new length in octets/bytes
       */
      void setLength(const uint64_t length);


      /** \brief checks whether this element is empty
       *
       * \return Returns true, if this element is empty.
       * Returns false, if it contains some data.
       */
      bool empty() const;


      /** \brief equality operator for Link
       *
       * \param other  the other instance
       * \return Returns true, if both instances are equal.
       */
      bool operator==(const Link& other) const;
    private:
      std::string m_href; /**< the link's IRI, mandatory */
      std::string m_rel; /**< link relation type, optional */
      std::string m_type; /**< media type, optional */
      std::string m_hreflang; /**< language of the resource */
      std::string m_title; /**< human-readable information about the link. optional */
      uint64_t m_length; /**< length of linked content in octets, optional */
  }; //class
} //namespace

#endif // ATOM10_LINK_HPP
