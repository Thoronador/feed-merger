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

#ifndef RSS20_PARSER_HPP
#define RSS20_PARSER_HPP

#include <string>
#include "../basic-rss/Parser.hpp"
#include "Channel.hpp"

//forward declarations
class XMLDocument;
class XMLNode;

namespace RSS20
{
  /** \brief parser for RSS 2.0 feeds
   */
  class Parser: public BasicRSS::Parser
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
  }; //class

} //namespace

#endif // RSS20_PARSER_HPP
