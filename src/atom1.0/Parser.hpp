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

#ifndef ATOM10_PARSER_HPP
#define ATOM10_PARSER_HPP

#include "Category.hpp"
#include "Link.hpp"
#include "PersonConstruct.hpp"

//forward declarations
class XMLDocument;
class XMLNode;

namespace Atom10
{
  class Parser
  {
    public:
      /** \brief parses a category from the given XML node
       *
       * \param categoryNode  the element node of the category
       * \param categoryInfo  variable that will be used to store the parsed result
       * \return Returns true, if the category could be parsed.
       * Returns false, if errors occurred.
       */
      static bool categoryFromNode(const XMLNode& categoryNode, Category& categoryInfo);


      /** \brief parses a link from the given XML node
       *
       * \param linkNode  the element node of the link
       * \param linkInfo  variable that will be used to store the parsed result
       * \return Returns true, if the link could be parsed.
       * Returns false, if an error occurred.
       */
      static bool linkFromNode(const XMLNode& linkNode, Link& linkInfo);

      /** \brief parses a person construct from the given XML node
       *
       * \param personConstructNode  the root node of the person construct
       * \param personInfo   variable that will be used to store the parsed result
       * \param nodeName  the name of the person construct's root node, e.g. "author"
       * \return Returns true, if the person construct could be parsed.
       * Returns false, if errors occurred.
       */
      static bool personConstructFromNode(const XMLNode& personConstructNode, PersonConstruct& personInfo, const std::string& nodeName);
    private:
  }; //class
} //namespace

#endif // ATOM10_PARSER_HPP
