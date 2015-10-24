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

namespace RSS20
{

bool Parser::fromFile(const std::string& fileName, Channel& feed)
{
  //parse XML file
  XMLDocument doc(fileName);
  if (!doc.isParsed())
  {
    std::cout << "Could not parse XML file!" << std::endl;
    return false;
  }
  //we don't want (and cannot use) empty files
  if (doc.isEmpty())
  {
    std::cout << "Empty XML document!" << std::endl;
    return false;
  }
  XMLNode node = doc.getRootNode();
  if (node.getNameAsString()!="rss")
  {
    std::cout << "Root element's name is not \"rss\" but \""
              << node.getNameAsString()<<"\" instead." << std::endl;
    return false;
  }

  if (node.getFirstAttributeName() != "version")
  {
    std::cout << "Root element has no \"version\" attribute!" << std::endl;
    return false;
  } //if
  if (node.getFirstAttributeValue() != "2.0")
  {
    std::cout << "Version of feed is not 2.0, but \""
              << node.getFirstAttributeValue() << "\"!" << std::endl;
    return false;
  }

  if (!node.hasChild())
  {
    std::cout << "No child nodes after root node.\n";
    return false;
  }

  node = node.getChild();

  //skip empty comment and text nodes
  while ((node.isCommentNode() or node.isTextNode())
         and (node.getContentBoth() == "") and node.hasNextSibling())
  {
    node = node.getNextSibling();
  } //while

  if (!node.isElementNode() or (node.getNameAsString() != "channel"))
  {
    std::cout << "Child node of <rss> node must be <channel> node! "
              << "However, node's name is " << node.getNameAsString() << "."
              << std::endl;
    std::cout << "Text node: " << node.isTextNode() << std::endl
              << "Value: " << node.getContentBoth() << std::endl;
    return false;
  }
  //get child node
  if (!node.hasChild())
  {
    std::cout << "Node <channel> has no child elements!";
    return false;
  }
  node = node.getChild();

  //initialize empty channel / feed
  feed = RSS20::Channel("", "", "", std::vector<Item>());

  while (node.hasNextSibling())
  {
    //Skip all non-element nodes (e.g. comment nodes).
    while (node.hasNextSibling() && !node.isElementNode())
    {
      node = node.getNextSibling();
    } //while (inner)

    const std::string nodeName = node.getNameAsString();

    if (nodeName == "title")
    {

    } //if title
    else if (nodeName == "link")
    {

    } //if link
    else if (nodeName == "description")
    {

    } //if description
    else if (nodeName == "item")
    {

    } //if item
    else
    {
      std::cout << "Found unexpected node name: \"" << nodeName << "\"!"
                << std::endl;
      return false;
    }

    node = node.getNextSibling();
  } //while (outer)

}

} //namespace
