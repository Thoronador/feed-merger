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
       * \param language      channel language
       * \param copyright     copyright notice for channel elements
       * \param managingEditor   managing editor's e-mail address
       * \param webMaster        webmaster's e-mail address
       * \param pubDate          publication date of the channel
       * \param lastBuildDate    time when the channel was last changed
       * \param category         category of the channel
       * \param generator        program used to generate the channel
       */
      Channel(const std::string& title, const std::string& link,
              const std::string& description, const std::vector<Item>& items = std::vector<Item>(),
              const std::string& language = "", const std::string& copyright = "",
              const std::string& managingEditor = "", const std::string& webMaster = "",
              const std::time_t pubDate = 0, const std::time_t lastBuildDate = 0,
              const Category& category = Category(), const std::string& generator = "");


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


      /** \brief gets the channel's language
       *
       * \return Returns the language.
       */
      const std::string& language() const;


      /** \brief sets the channel's language
       *
       * \param language  the new channel language
       */
      void setLanguage(const std::string& language);


      /** \brief gets the channel's copyright note
       *
       * \return Returns the copyright note.
       */
      const std::string& copyright() const;


      /** \brief sets the channel's copyright notice
       *
       * \param copyright  the new channel copyright notice
       */
      void setCopyright(const std::string& copyright);


      /** \brief gets the channel's managing editor's e-mail address
       *
       * \return Returns the managing editor's e-mail address.
       */
      const std::string& managingEditor() const;


      /** \brief sets the channel's managing editor's e-mail address
       *
       * \param managingEditor  the new channel's managing editor's e-mail address
       */
      void setManagingEditor(const std::string& managingEditor);


      /** \brief gets the channel's webmaster's e-mail address
       *
       * \return Returns the webmaster's e-mail address.
       */
      const std::string& webMaster() const;


      /** \brief sets the channel's webmaster's e-mail address
       *
       * \param webMaster  the new channel's webmaster's e-mail address
       */
      void setWebMaster(const std::string& webMaster);


      /** \brief gets the channel's publication date
       *
       * \return Returns the publication date.
       * Returns (time_t)0, if no publication date was set.
       */
      std::time_t pubDate() const;


      /** \brief sets the channel's publication date
       *
       * \param pubDate  the new publication date of the channel
       */
      void setPubDate(const std::time_t pubDate);


      /** \brief gets the time the content of the channel changed
       *
       * \return Returns the time the content of the channel changed.
       * Returns (time_t)0, if no date was set.
       */
      std::time_t lastBuildDate() const;


      /** \brief sets the channel's time the content of the channel changed
       *
       * \param lastBuildDate  the new time the content of the channel changed
       */
      void setLastBuildDate(const std::time_t lastBuildDate);


      /** \brief gets the channel's category
       *
       * \return Returns the category.
       */
      const Category& category() const;


      /** \brief sets the channel's category
       *
       * \param category  the new channel category
       */
      void setCategory(const Category& category);


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


      /** \brief equality operator for RSS 2.0 channel instances
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
      std::string m_language; /**< language the channel is written in */
      std::string m_copyright; /**< copyright notice for channel */
      std::string m_managingEditor; /**< e-mail address for person responsible for editorial content */
      std::string m_webMaster; /**< e-mail address for person responsible for technical issues relating to channel */
      std::time_t m_pubDate; /**< publication date for content in the channel */
      std::time_t m_lastBuildDate; /**< last time the content of the channel changed */
      Category m_category; /**< the channel's category */
      std::string m_generator; /**< program that was used to generate the channel */
      #warning TODO: implement missing optional channel elements!
  }; //class
} //namespace

#endif // RSS20_CHANNEL_HPP
