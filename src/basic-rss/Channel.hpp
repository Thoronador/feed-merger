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

#ifndef BASIC_RSS_CHANNEL_HPP
#define BASIC_RSS_CHANNEL_HPP

#include <ctime>
#include <set>
#include <string>
#include <vector>
#include "Days.hpp"
#include "Image.hpp"
#include "TextInput.hpp"

namespace BasicRSS
{
  /** \brief contains common channel elements for RSS 0.91 and RSS 2.0
   */
  class Channel
  {
    public:
      /** \brief constant value that indicates an unset date
       */
      static const std::time_t NoDate;


      /** \brief default constructor - Sets all members to an empty state.
       */
      Channel();


      /** \brief constructor with option to pass parameters
       *
       * \param title  title of the channel
       * \param link   link URL
       * \param description   channel description
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
              const std::string& description, const std::string& language,
              const std::string& copyright = "", const std::string& managingEditor = "",
              const std::string& webMaster = "",
              const std::time_t pubDate = NoDate, const std::time_t lastBuildDate = NoDate,
              const std::string& docs = "", const Image& image = Image(),
              const std::string& rating = "", const TextInput& textInput = TextInput(),
              const std::set<unsigned int>& skipHours = std::set<unsigned int>(),
              const std::set<Days>& skipDays = std::set<Days>());


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
       * Returns NoDate, if no publication date was set.
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
       * Returns NoDate, if no date was set.
       */
      std::time_t lastBuildDate() const;


      /** \brief sets the channel's time the content of the channel changed
       *
       * \param lastBuildDate  the new time the content of the channel changed
       */
      void setLastBuildDate(const std::time_t lastBuildDate);


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


      /** \brief gets the hours (in GMT) where aggregators shall skip querying the channel
       *
       * \return Returns the set of hours (range [0;23]).
       */
      const std::set<unsigned int>& skipHours() const;


      /** \brief sets the skip hours
       *
       * \param skipHours  the new set of hours
       */
      void setSkipHours(const std::set<unsigned int>& skipHours);


      /** \brief gets the days (in GMT) where aggregators shall skip querying the channel
       *
       * \return Returns the set of days.
       */
      const std::set<Days>& skipDays() const;


      /** \brief sets the skip days
       *
       * \param skipDays  the new set of days
       */
      void setSkipDays(const std::set<Days>& skipDays);


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
      std::string m_title; /**< title of the channel */
      std::string m_link; /**< link */
      std::string m_description; /**< channel description */
      std::string m_language; /**< language the channel is written in */
      std::string m_copyright; /**< copyright notice for channel */
      std::string m_managingEditor; /**< e-mail address for person responsible for editorial content */
      std::string m_webMaster; /**< e-mail address for person responsible for technical issues relating to channel */
      std::time_t m_pubDate; /**< publication date for content in the channel */
      std::time_t m_lastBuildDate; /**< last time the content of the channel changed */
      std::string m_docs; /**< URL for format documentation */
      Image m_image; /**< graphic that can be displayed with the channel */
      std::string m_rating; /**< the PICS rating for the channel */
      TextInput m_textInput; /**< text input box that can be displayed with the channel */
      std::set<unsigned int> m_skipHours; /**< hint for aggregators telling them which hours they can skip */
      std::set<Days> m_skipDays; /**< hint for aggregators telling them which days they can skip */
  }; //class
} //namespace

#endif // BASIC_RSS_CHANNEL_HPP
