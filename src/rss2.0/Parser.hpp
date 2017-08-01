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

#include <string>
#include "Channel.hpp"

#ifndef RSS20_PARSER_HPP
#define RSS20_PARSER_HPP

//forward declarations
class XMLDocument;
class XMLNode;

namespace RSS20
{

  class Parser
  {
    public:
      /** \brief parses the given file as RSS 2.0 feed
       *
       * \param fileName  the name of the file
       * \param feed      variable that will be used to store the parsed result
       * \return Returns true, if the file could be parsed.
       * Returns false, if the file could not be parsed.
       */
      static bool fromFile(const std::string& fileName, Channel& feed);


      /** \brief parses the given XML document as RSS 2.0 feed
       *
       * \param doc   the XML document
       * \param feed  variable that will be used to store the parsed result
       * \return Returns true, if the document could be parsed as RSS 2.0.
       * Returns false, if the document could not be parsed.
       */
      static bool fromDocument(const XMLDocument& doc, Channel& feed);


      /** \brief parses the given string as RSS 2.0 feed
       *
       * \param source  source code of the RSS 2.0 feed
       * \param feed  variable that will be used to store the parsed result
       * \return Returns true, if the string could be parsed as RSS 2.0.
       * Returns false, if the string could not be parsed.
       */
      static bool fromString(const std::string& source, Channel& feed);
    private:
      /** \brief parses a feed item from the given XML node
       *
       * \param itemNode  the <item> node
       * \param theItem   variable that will be used to store the parsed result
       * \return Returns true, if the item node could be parsed.
       * Returns false, if errors occurred.
       */
      static bool itemFromNode(const XMLNode& itemNode, Item& theItem);


      /** \brief parses a cloud element from the given XML node
       *
       * \param cloudNode  the <cloud> node
       * \param cloudInfo   variable that will be used to store the parsed result
       * \return Returns true, if the cloud node could be parsed.
       * Returns false, if errors occurred.
       */
      static bool cloudFromNode(const XMLNode& cloudNode, Cloud& cloudInfo);


      /** \brief parses a enclosure element from the given XML node
       *
       * \param enclosureNode  the <enclosure> node
       * \param enclosureInfo   variable that will be used to store the parsed result
       * \return Returns true, if the enclosure node could be parsed.
       * Returns false, if errors occurred.
       */
      static bool enclosureFromNode(const XMLNode& enclosureNode, Enclosure& enclosureInfo);


      /** \brief parses an image element from the given XML node
       *
       * \param imageNode  the <image> node
       * \param imageInfo   variable that will be used to store the parsed result
       * \return Returns true, if the image node could be parsed.
       * Returns false, if errors occurred.
       */
      static bool imageFromNode(const XMLNode& imageNode, Image& imageInfo);


      /** \brief parses a source element from the given XML node
       *
       * \param sourceNode  the <source> node
       * \param sourceInfo   variable that will be used to store the parsed result
       * \return Returns true, if the source node could be parsed.
       * Returns false, if errors occurred.
       */
      static bool sourceFromNode(const XMLNode& sourceNode, Source& sourceInfo);


      /** \brief parses a category element from the given XML node
       *
       * \param categoryNode  the <category> node
       * \param categoryInfo   variable that will be used to store the parsed result
       * \return Returns true, if the category node could be parsed.
       * Returns false, if errors occurred.
       */
      static bool categoryFromNode(const XMLNode& categoryNode, Category& categoryInfo);


      /** \brief parses a textInput element from the given XML node
       *
       * \param textInputNode  the <textInput> node
       * \param textInputInfo   variable that will be used to store the parsed result
       * \return Returns true, if the textInput node could be parsed.
       * Returns false, if errors occurred.
       */
      static bool textInputFromNode(const XMLNode& textInputNode, TextInput& textInputInfo);


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
  }; //class

} //namespace

#endif // RSS20_PARSER_HPP
