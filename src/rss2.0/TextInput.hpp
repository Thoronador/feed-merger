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

#ifndef RSS20_TEXTINPUT_HPP
#define RSS20_TEXTINPUT_HPP

#include <string>

namespace RSS20
{
  /** \brief class to represent the textInput element of an RSS 2.0 channel
   *
   * \remarks Use of the textInput element in RSS feeds is discouraged by the
   * specification, because it is rarely supported by feed readers and most of
   * them just ignore it.
   */
  class TextInput
  {
    public:
      /** \brief default constructor - Sets all members to an empty state.
       */
      TextInput();


      /** \brief constructor with option to pass initial values
       *
       * \param title        label of the submit button
       * \param description  explanation of the text input area
       * \param name         name of the text object
       * \param link         URL of the (CGI) script that processes the requests
       */

      TextInput(const std::string& title, const std::string& description,
                const std::string& name, const std::string& link);


      /** \brief gets the input item's title
       *
       * \return Returns the title.
       */
      const std::string& title() const;


      /** \brief sets the text input's title
       *
       * \param title  the new text input title
       */
      void setTitle(const std::string& title);


      /** \brief gets the text input description
       *
       * \return Returns the description.
       */
      const std::string& description() const;


      /** \brief sets the text input description
       *
       * \param description  the new text input description
       */
      void setDescription(const std::string& description);


      /** \brief gets the name of the form component
       *
       * \return Returns the name.
       */
      const std::string& name() const;


      /** \brief sets the name
       *
       * \param name  the new name
       */
      void setName(const std::string& name);


      /** \brief gets the URL of the processing script
       *
       * \return Returns the script URL.
       */
      const std::string& link() const;


      /** \brief sets the URL of the processing script
       *
       * \param link  the new URL
       */
      void setLink(const std::string& link);


      /** \brief checks whether this element is empty
       *
       * \return Returns true, if this element is empty.
       * Returns false, if it contains all required data.
       */
      bool empty() const;


      /** \brief equality operator for RSS 2.0 textInput elements
       *
       * \param other   the other textInput elements
       * \return Returns true, if this instance and other are equal.
       */
      bool operator==(const TextInput& other) const;
    private:
      std::string m_title; /**< label of the submit button */
      std::string m_description; /**< explains the text input area */
      std::string m_name; /**< name of the text object */
      std::string m_link; /**< URL of the (CGI) script that processes the requests */
  }; //class
} //namespace

#endif // RSS20_TEXTINPUT_HPP
