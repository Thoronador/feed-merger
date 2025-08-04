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

#ifndef RSS20_ITEM_HPP
#define RSS20_ITEM_HPP

#include <ctime>
#include <set>
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
       * \param category    category element(s) of the item
       * \param comments    comment URL of the item
       * \param enclosure   enclosure of the item
       * \param guid        guid of the item
       * \param pubDate     publication date of the item
       * \param source      source date of the item
       */
      Item(const std::string& title, const std::string& link,
           const std::string& description, const std::string& author,
           const std::set<Category>& category, const std::string& comments,
           const Enclosure& enclosure, const GUID& guid,
           const std::time_t pubDate, const Source& source);


      /** \brief gets the item's title
       *
       * \return Returns the value of the title element.
       */
      const std::string& title() const;


      /** \brief sets the item's title
       *
       * \param title  the new item title
       */
      void setTitle(const std::string& title);


      /** \brief gets the item's link
       *
       * \return Returns the value of the link element.
       */
      const std::string& link() const;


      /** \brief sets the item link
       *
       * \param link  the new item link URL
       */
      void setLink(const std::string& link);


      /** \brief gets the item's description
       *
       * \return Returns the value of the description element.
       */
      const std::string& description() const;


      /** \brief sets the item's description
       *
       * \param description  the new item description
       */
      void setDescription(const std::string& description);


      /** \brief gets the item's author
       *
       * \return Returns the value of the author element.
       */
      const std::string& author() const;


      /** \brief sets the item's author
       *
       * \param author  the new item author
       */
      void setAuthor(const std::string& author);


      /** \brief gets the item's category
       *
       * \return Returns the value(s) of the category element(s).
       */
      const std::set<Category>& category() const;


      /** \brief sets the item's categories
       *
       * \param category  the new item category set
       */
      void setCategory(const std::set<Category>& category);


      /** \brief adds a new item category to the existing categories
       *
       * \param category  the item category which shall be added
       */
      void addCategory(const Category& category);


      /** \brief gets the item's comment URL
       *
       * \return Returns the value of the comment element.
       */
      const std::string& comments() const;


      /** \brief sets the item's comment URL
       *
       * \param comment  the new comment URL
       */
      void setComments(const std::string& comment);


      /** \brief gets the item's enclosure
       *
       * \return Returns the data of the enclosure element.
       */
      const Enclosure& enclosure() const;


      /** \brief sets the item's enclosure
       *
       * \param enclosure  the new enclosure
       */
      void setEnclosure(const Enclosure& enclosure);


      /** \brief gets the item's GUID
       *
       * \return Returns the value of the guid element.
       */
      const GUID& guid() const;


      /** \brief sets the item's GUID
       *
       * \param guid  the new GUID
       */
      void setGUID(const GUID& guid);


      /** \brief gets the item's publication date
       *
       * \return Returns the value of the pubDate element.
       */
      std::time_t pubDate() const;


      /** \brief sets the item's publication date
       *
       * \param pubDate  the new publication date
       */
      void setPubDate(const std::time_t& pubDate);


      /** \brief gets the item's source
       *
       * \return Returns the value of the source element.
       */
      const Source& source() const;


      /** \brief sets the item's source
       *
       * \param source  the new source
       */
      void setSource(const Source& source);


      /** \brief checks whether this item is empty
       *
       * \return Returns true, if this item is empty.
       * Returns false, if it contains some data.
       */
      bool empty() const;


      /** \brief equality operator for Item instances
       *
       * \param other   the other Item
       * \return Returns true, if this instance and other are equal.
       */
      bool operator==(const Item& other) const;


      /** \brief "less than" comparison (compares publication dates only!)
       *
       * \param other  the other Item
       * \return Returns true, if the the Item's publication date was before
       * the other Item's publication date.
       */
      bool operator<(const Item& other) const;


      /** \brief "greater than" comparison (compares publication dates only!)
       *
       * \param other  the other Item
       * \return Returns true, if the the Item's publication date was after
       * the other Item's publication date.
       */
      bool operator>(const Item& other) const;
    private:
      std::string m_title; /**< title of the item */
      std::string m_link; /**< link URL */
      std::string m_description; /**< description, if any */
      std::string m_author; /**< author of the linked item */
      std::set<Category> m_category; /**< the item's categories */
      std::string m_comments; /**< URL to the comment section / website */
      Enclosure m_enclosure; /**< enclosure */
      GUID m_guid; /**< the item's GUID */
      std::time_t m_pubDate; /**< publication date */
      Source m_source; /**< source element */
  }; //class
} //namespace

#endif // RSS20_ITEM_HPP
