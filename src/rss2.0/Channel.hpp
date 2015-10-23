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

#ifndef RSS20_CHANNEL_HPP
#define RSS20_CHANNEL_HPP

#include <string>
#include <vector>
#include "Item.hpp"

namespace RSS20
{

  class Channel
  {
    public:
      /** \brief default constructor
       *
       * \param title  title of the channel
       * \param link   link URL
       * \param description   channel description
       * \param items         initial items in channel
       */
      Channel(const std::string& title, const std::string& link,
              const std::string& description, const std::vector<Item>& items = std::vector<Item>());


      /** \brief gets the channel's title
       *
       * \return Returns the title.
       */
      const std::string& title() const;


      /** \brief sets the channel's title
       *
       * \param title  the new channel title
       */
      void setTitle(const std::string& title);


      /** \brief gets the channel link
       *
       * \return Returns the link URL.
       */
      const std::string& link() const;


      /** \brief sets the channel link
       *
       * \param link  the new channel link URL
       */
      void setLink(const std::string& link);


      /** \brief gets the channel's description
       *
       * \return Returns the description.
       */
      const std::string& description() const;


      /** \brief sets the channel's description
       *
       * \param description  the new channel description
       */
      void setDescription(const std::string& description);


      /** \brief returns the current item collection
       *
       * \return STL container that holds the items
       */
      const std::vector<Item>& items() const;


      /** \brief add a new item to the channel
       *
       * \param item  the new item, must not be empty
       */
      void addItem(const Item& item);


      /** \brief equality operat for RSS 2.0 channel instances
       *
       * \param other   the other channel
       * \return Returns true, if this instance and other are equal.
       */
      bool operator==(const Channel& other) const;
    private:
      //required elements; title, link, description
      std::string m_title; /**< title of the channel */
      std::string m_link; /**< link */
      std::string m_description; /**< channel description */
      //channel items
      std::vector<Item> m_items; /**< channel items */
      //optional elements
      #warning TODO: implement optional channel elements!
  }; //class
} //namespace

#endif // RSS20_CHANNEL_HPP
