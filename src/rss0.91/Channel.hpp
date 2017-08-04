/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger.
    Copyright (C) 2015, 2017  Dirk Stolle

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

#ifndef RSS091_CHANNEL_HPP
#define RSS091_CHANNEL_HPP

#include <set>
#include <string>
#include <vector>
#include "../basic-rss/Channel.hpp"
#include "../basic-rss/Days.hpp"
#include "Image.hpp"
#include "Item.hpp"
#include "TextInput.hpp"

namespace RSS091
{
  /** \brief RSS 0.91 channel
   */
  class Channel: public BasicRSS::Channel
  {
    public:
      /** \brief default constructor - Sets all members to an empty state.
       */
      Channel();


      /** \brief constructor with option to pass parameters
       *
       * \param title  title of the channel
       * \param link   link URL
       * \param description   channel description
       * \param items         initial items in channel
       * \param language      channel language
       * \param copyright     copyright notice for channel elements
       * \param managingEditor   managing editor's e-mail address
       * \param webMaster        webmaster's e-mail address
       * \param pubDate          publication date of the channel
       * \param lastBuildDate    time when the channel was last changed
       * \param docs             format documentation URL
       * \param image            channel image information
       * \param rating           the PICS rating of the channel
       * \param textInput        text input box that can be displayed with the channel
       * \param skipHours        initial value for skipHours element
       * \param skipDays         initial value for skipDays element
       */
      Channel(const std::string& title, const std::string& link,
              const std::string& description, const std::vector<Item>& items = std::vector<Item>(),
              const std::string& language = "", const std::string& copyright = "",
              const std::string& managingEditor = "", const std::string& webMaster = "",
              const std::time_t pubDate = 0, const std::time_t lastBuildDate = 0,
              const std::string& docs = "", const Image& image = Image(),
              const std::string& rating = "", const TextInput& textInput = TextInput(),
              const std::set<unsigned int>& skipHours = std::set<unsigned int>(),
              const std::set<BasicRSS::Days>& skipDays = std::set<BasicRSS::Days>());


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


      /** \brief equality operator for RSS 2.0 channel instances
       *
       * \param other   the other channel
       * \return Returns true, if this instance and other are equal.
       */
      bool operator==(const Channel& other) const;


      /** \brief inequality operator for RSS 2.0 channel instances
       *
       * \param other   the other channel
       * \return Returns true, if this instance and other are NOT equal.
       */
      bool operator!=(const Channel& other) const;
    private:
      //required elements; title, link, description
      // --> declared in base class
      //channel items
      std::vector<Item> m_items; /**< channel items */
      //optional elements
      // --> declared in base class
  }; //class
} //namespace

#endif // RSS091_CHANNEL_HPP
