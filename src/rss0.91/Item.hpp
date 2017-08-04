/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger.
    Copyright (C) 2017  Dirk Stolle

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

#ifndef RSS091_ITEM_HPP
#define RSS091_ITEM_HPP

#include <string>

namespace RSS091
{
  /** \brief class to hold an RSS 0.91 feed item
   */
  class Item
  {
    public:
      /** \brief default constructor
       *
       * \param title  the item's title
       * \param link   link of the item
       * \param description description of the item (optional)
       */
      Item(const std::string& title, const std::string& link,
           const std::string& description = "");


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
    private:
      std::string m_title; /**< title of the item */
      std::string m_link; /**< link URL */
      std::string m_description; /**< description, if any */
  }; //class
} //namespace

#endif // RSS091_ITEM_HPP
