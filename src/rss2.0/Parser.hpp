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
  }; //class

} //namespace

#endif // RSS20_PARSER_HPP
