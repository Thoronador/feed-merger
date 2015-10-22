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

#ifndef RSS20_ITEM_HPP
#define RSS20_ITEM_HPP

#include <ctime>
#include <string>
#include "Category.hpp"
#include "Enclosure.hpp"
#include "Guid.hpp"
#include "Source.hpp"

namespace RSS20
{
  /** \brief class to hold an RSS 2.0 feed item
   */
  class Item
  {
    public:
      /** \brief default constructor
       *
       * \param title  the item's title
       * \param link   link of the item
       * \param description description of the item
       * \param author      author of the item
       * \param category    category of the item
       * \param comments    comment URL of the item
       * \param enclosure   enclosure of the item
       * \param guid        guid of the item
       * \param pubDate     publication date of the item
       * \param source      source date of the item
       */
      Item(const std::string& title, const std::string& link,
           const std::string& description, const std::string& author,
           const Category& category, const std::string& comments,
           const Enclosure& enclosure, const GUID& guid,
           const std::time_t pubDate, const Source& source);


      /** \brief gets the item's title
       *
       * \return Returns the value of the title element.
       */
      const std::string& title() const;


      /** \brief gets the item's link
       *
       * \return Returns the value of the link element.
       */
      const std::string& link() const;


      /** \brief gets the item's description
       *
       * \return Returns the value of the description element.
       */
      const std::string& description() const;


      /** \brief gets the item's author
       *
       * \return Returns the value of the author element.
       */
      const std::string& author() const;


      /** \brief gets the item's category
       *
       * \return Returns the value of the category element.
       */
      const Category& category() const;

      /** \brief gets the item's comment URL
       *
       * \return Returns the value of the comment element.
       */
      const std::string& comments() const;


      /** \brief gets the item's enclosure
       *
       * \return Returns the data of the enclosure element.
       */
      const Enclosure& enclosure() const;


      /** \brief gets the item's GUID
       *
       * \return Returns the value of the guid element.
       */
      const GUID& guid() const;


      /** \brief gets the item's publication date
       *
       * \return Returns the value of the pubDate element.
       */
      const std::time_t pubDate() const;


      /** \brief gets the item's source
       *
       * \return Returns the value of the source element.
       */
      const Source& source() const;
    private:
      std::string m_title; /**< title of the item */
      std::string m_link; /**< link URL */
      std::string m_description; /**< description, if any */
      std::string m_author; /**< author of the linked item */
      Category m_category; /**< the item's category */
      std::string m_comments; /**< URL to the comment section / website */
      Enclosure m_enclosure; /**< enclosure */
      GUID m_guid; /**< the item's GUID */
      std::time_t m_pubDate; /**< publication date */
      Source m_source; /**< source element */
  }; //class
} //namespace

#endif // RSS20_ITEM_HPP
