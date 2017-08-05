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

#ifndef BASIC_RSS_PARSER_HPP
#define BASIC_RSS_PARSER_HPP

#include <set>
#include "Channel.hpp"
#include "Days.hpp"
#include "Image.hpp"
#include "TextInput.hpp"

//forward declarations
class XMLDocument;
class XMLNode;

namespace BasicRSS
{
  /** \brief common XML parsing methods for RSS 0.91 and RSS 2.0
   */
  class Parser
  {
    protected:
      /** \brief parses an image element from the given XML node
       *
       * \param imageNode  the <image> node
       * \param imageInfo   variable that will be used to store the parsed result
       * \return Returns true, if the image node could be parsed.
       * Returns false, if errors occurred.
       */
      static bool imageFromNode(const XMLNode& imageNode, Image& imageInfo);


      /** \brief parses a textInput element from the given XML node
       *
       * \param textInputNode  the <textInput> (RSS 2.0) / <textinput> (RSS 0.91) node
       * \param textInputInfo  variable that will be used to store the parsed result
       * \param rss091         whether it is an RSS 0.91 feed
       * \return Returns true, if the textInput node could be parsed.
       * Returns false, if errors occurred.
       */
      static bool textInputFromNode(const XMLNode& textInputNode, TextInput& textInputInfo, const bool rss091 = false);


      /** \brief parses a skipHours element from the given XML node
       *
       * \param skipHoursNode  the <skipHours> node
       * \param skipHoursInfo   variable that will be used to store the parsed result
       * \return Returns true, if the skipHours node could be parsed.
       * Returns false, if errors occurred.
       */
      static bool skipHoursFromNode(const XMLNode& skipHoursNode, std::set<unsigned int>& skipHoursInfo);


      /** \brief parses a skipDays element from the given XML node
       *
       * \param skipDaysNode   the <skipDays> node
       * \param skipDaysInfo   variable that will be used to store the parsed result
       * \return Returns true, if the skipDays node could be parsed.
       * Returns false, if errors occurred.
       */
      static bool skipDaysFromNode(const XMLNode& skipDaysNode, std::set<Days>& skipDaysInfo);


      /** \brief tries to parse a channel element that is common in RSS 0.91 and RSS 2.0
       *
       * \param node  the current XML element node
       * \param feed  the RSS feed
       * \param errorFlag  flag that is set to true, if an error occurred
       * \return Returns true, if a common channel element was parsed.
       *         Returns false otherwise.
       */
      static bool commonChannelElementFromNode(const XMLNode& node, Channel& feed, bool& errorFlag);
  }; //class

} //namespace

#endif // BASIC_RSS_PARSER_HPP
