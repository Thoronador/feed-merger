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

#include "Parser.hpp"
#include <iostream>
#include "../xml/XMLDocument.hpp"

namespace Atom10
{

bool Parser::personConstructFromNode(const XMLNode& personConstructNode, PersonConstruct& personInfo, const std::string& nodeName)
{
  if (!personConstructNode.isElementNode() or (personConstructNode.getNameAsString() != nodeName))
    return false;

  if (!personConstructNode.hasChild())
    return false;

  XMLNode child = personConstructNode.getChild();

  personInfo = PersonConstruct();

  while (child.hasNextSibling())
  {
    child.skipEmptyCommentAndTextSiblings();

    if (!child.isElementNode())
    {
      std::cout << "Parser::personConstructFromNode: Expected element node, but current"
                << " node is not an element node!" << std::endl;
      return false;
    }

    const std::string nodeName = child.getNameAsString();
    if (nodeName == "name")
    {
      if (!personInfo.name().empty())
      {
        std::cout << "Person construct already has a name!" << std::endl;
        return false;
      } //if name was already specified
      personInfo.setName(child.getContentBoth());
    }
    else if (nodeName == "uri")
    {
      if (!personInfo.uri().empty())
      {
        std::cout << "Person construct already has an URI!" << std::endl;
        return false;
      } //if URI was already specified
      personInfo.setUri(child.getContentBoth());
    }
    else if (nodeName == "email")
    {
      if (!personInfo.email().empty())
      {
        std::cout << "Person construct already has an e-mail address!" << std::endl;
        return false;
      } //if e-mail was already specified
      personInfo.setEmail(child.getContentBoth());
    }
    else
    {
      std::cout << "Found unexpected node name within person construct: \"" << nodeName
                << "\"!" << std::endl;
      return false;
    }
    child = child.getNextSibling();
  } //while
  //We are done here. Person construct should not be empty by now.
  return (!personInfo.empty());
}

} //namespace
