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

#ifndef RSS20_CHANNEL_HPP
#define RSS20_CHANNEL_HPP

#include <set>
#include <string>
#include <vector>
#include "../basic-rss/Channel.hpp"
#include "../basic-rss/Days.hpp"
#include "Cloud.hpp"
#include "Image.hpp"
#include "Item.hpp"
#include "TextInput.hpp"

namespace RSS20
{

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
       * \param category         category element(s) of the channel
       * \param generator        program used to generate the channel
       * \param docs             format documentation URL
       * \param cloud  cloud information for lightweight publish-subscribe protocol
       * \param ttl              "time to live" (minutes)
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
              const std::set<Category>& category = std::set<Category>(), const std::string& generator = "",
              const std::string& docs = "", const Cloud& cloud = Cloud(),
              const int ttl = -1, const Image& image = Image(),
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


      /** \brief sets the list of items in the feed
       *
       * \param all   vector of feed items
       */
      void setItems(const std::vector<Item>& all);


      /** \brief gets the channel's category element(s)
       *
       * \return Returns the category elements.
       */
      const std::set<Category>& category() const;


      /** \brief sets the channel's category elements
       *
       * \param category  the new channel categories
       */
      void setCategory(const std::set<Category>& category);


      /** \brief adds a new channel category to the existing categories
       *
       * \param category  the item category which shall be added
       */
      void addCategory(const Category& category);


      /** \brief gets the channel's language
       *
       * \return Returns the language.
       */
      const std::string& generator() const;


      /** \brief sets the channel's generator
       *
       * \param generator  the new channel generator
       */
      void setGenerator(const std::string& generator);


      /** \brief gets the cloud information for publish-subscribe protocol
       *
       * \return Returns the cloud information.
       */
      const Cloud& cloud() const;


      /** \brief sets the cloud information for publish-subscribe protocol
       *
       * \param cloud  the new cloud information
       */
      void setCloud(const Cloud& cloud);


      /** \brief gets the TTL (time to live) in minutes
       *
       * \return Returns the TTL in minutes.
       *         Returns a negative value, if no TTL was set.
       */
      int ttl() const;


      /** \brief sets the time to live (TTL) in minutes
       *
       * \param title  the new time to live (TTL) in minutes
       */
      void setTtl(const int ttl);


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
      //required elements: title, link, description: declared in base class
      //channel items
      std::vector<Item> m_items; /**< channel items */
      //optional elements
      std::set<Category> m_category; /**< the channel's categories */
      std::string m_generator; /**< program that was used to generate the channel */
      Cloud m_cloud; /**< cloud information for lightweight publish-subscribe protocol */
      int m_ttl; /**< number of minutes that indicates how long a channel can be cached before refreshing from the source */
  }; //class
} //namespace

#endif // RSS20_CHANNEL_HPP
