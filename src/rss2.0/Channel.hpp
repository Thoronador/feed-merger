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
#include "Cloud.hpp"
#include "Image.hpp"
#include "Item.hpp"
#include "TextInput.hpp"

namespace RSS20
{

  class Channel
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
       * \param category         category of the channel
       * \param generator        program used to generate the channel
       * \param docs             format documentation URL
       * \param cloud  cloud information for lightweight publish-subscribe protocol
       * \param ttl              "time to live" (minutes)
       * \param image            channel image information
       * \param rating           the PICS rating of the channel
       * \param textInput        text input box that can be displayed with the channel
       */
      Channel(const std::string& title, const std::string& link,
              const std::string& description, const std::vector<Item>& items = std::vector<Item>(),
              const std::string& language = "", const std::string& copyright = "",
              const std::string& managingEditor = "", const std::string& webMaster = "",
              const std::time_t pubDate = 0, const std::time_t lastBuildDate = 0,
              const Category& category = Category(), const std::string& generator = "",
              const std::string& docs = "", const Cloud& cloud = Cloud(),
              const int ttl = -1, const Image& image = Image(),
              const std::string& rating = "", const TextInput& textInput = TextInput());


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


      /** \brief gets the format documentation URL
       *
       * \return Returns the format documentation URL.
       */
      const std::string& docs() const;


      /** \brief sets the format documentation URL
       *
       * \param title  the new format documentation URL
       */
      void setDocs(const std::string& docs);


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


      /** \brief gets the channel's image
       *
       * \return Returns the channel image (if any was set).
       */
      const Image& image() const;


      /** \brief sets the channel image information
       *
       * \param image  the new image information
       */
      void setImage(const Image& image);


      /** \brief gets the PICS rating for the channel
       *
       * \return Returns the PICS rating for the channel.
       */
      const std::string& rating() const;


      /** \brief sets the PICS rating for the channel
       *
       * \param rating  the new PICS rating
       */
      void setRating(const std::string& rating);


      /** \brief gets the text input box for the channel
       *
       * \return Returns the text input box for the channel.
       */
      const TextInput& textInput() const;


      /** \brief sets the text input box for the channel
       *
       * \param textInput  the new text input box
       */
      void setTextInput(const TextInput& textInput);

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
      std::string m_docs; /**< URL for format documentation */
      Cloud m_cloud; /**< cloud information for lightweight publish-subscribe protocol */
      int m_ttl; /**< number of minutes that indicates how long a channel can be cached before refreshing from the source */
      Image m_image; /**< graphic that can be displayed with the channel */
      std::string m_rating; /**< the PICS rating for the channel */
      TextInput m_textInput; /**< text input box that can be displayed with the channel */
      #warning TODO: implement missing optional channel elements!
  }; //class
} //namespace

#endif // RSS20_CHANNEL_HPP
