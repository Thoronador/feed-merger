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

#include "Parser.hpp"
#include <iostream>
#include "../rfc822/Date.hpp"
#include "../StringFunctions.hpp"
#include "../xml/XMLDocument.hpp"
#include "Channel.hpp"

namespace RSS091
{

bool Parser::itemFromNode(const XMLNode& itemNode, Item& theItem)
{
  if (!itemNode.isElementNode() or (itemNode.getNameAsString() != "item"))
    return false;

  theItem = Item("", "", "");

  if (!itemNode.hasChild())
    return false;

  XMLNode child = itemNode.getChild();

  while (child.hasNextSibling())
  {
    child.skipEmptyCommentAndTextSiblings();

    if (!child.isElementNode())
    {
      std::cerr << "Parser::itemFromNode: Expected element node, but current"
                << " XML node is not an element node!" << std::endl;
      return false;
    }

    const std::string nodeName = child.getNameAsString();

    if (nodeName == "title")
    {
      if (!theItem.title().empty())
      {
        std::cerr << "Item already has a title!" << std::endl;
        return false;
      } //if title was already specified
      theItem.setTitle(child.getContentBoth());
    }
    else if (nodeName == "link")
    {
      if (!theItem.link().empty())
      {
        std::cerr << "Item already has a link!" << std::endl;
        return false;
      } //if link was already specified
      theItem.setLink(child.getContentBoth());
    }
    else if (nodeName == "description")
    {
      if (!theItem.description().empty())
      {
        std::cerr << "Item already has a description!" << std::endl;
        return false;
      } //if description was already specified
      theItem.setDescription(child.getContentBoth());
    }
    else
    {
      std::cerr << "Found unexpected node name within item: \"" << nodeName
                << "\"!" << std::endl;
      return false;
    }
    child = child.getNextSibling();
  } //while
  //We are done here. Item should not be empty by now.
  return (!theItem.empty());
}

bool Parser::fromFile(const std::string& fileName, Channel& feed)
{
  //parse XML file
  const XMLDocument doc(fileName);
  return fromDocument(doc, feed);
}

bool Parser::fromString(const std::string& source, Channel& feed)
{
  if (source.empty())
    return false;
  XMLDocument doc(xmlParseDoc(reinterpret_cast<const xmlChar*>(source.c_str())));
  return fromDocument(doc, feed);
}

bool Parser::fromDocument(const XMLDocument& doc, Channel& feed)
{
  if (!doc.isParsed())
  {
    std::cerr << "Could not parse XML file!" << std::endl;
    return false;
  }
  //we don't want (and cannot use) empty files
  if (doc.isEmpty())
  {
    std::cerr << "Empty XML document!" << std::endl;
    return false;
  }
  XMLNode node = doc.getRootNode();
  if (node.getNameAsString() != "rss")
  {
    std::cerr << "Root element's name is not \"rss\" but \""
              << node.getNameAsString() << "\" instead." << std::endl;
    return false;
  }

  if (node.getFirstAttributeName() != "version")
  {
    std::cerr << "Root element has no \"version\" attribute!" << std::endl;
    return false;
  } //if
  if (node.getFirstAttributeValue() != "0.91")
  {
    std::cerr << "Version of feed is not 0.91, but \""
              << node.getFirstAttributeValue() << "\"!" << std::endl;
    return false;
  }

  if (!node.hasChild())
  {
    std::cerr << "No child nodes after root node.\n";
    return false;
  }

  node = node.getChild();

  //skip empty comment and text nodes
  node.skipEmptyCommentAndTextSiblings();

  if (!node.isElementNode() or (node.getNameAsString() != "channel"))
  {
    std::cerr << "Child node of <rss> node must be <channel> node! "
              << "However, node's name is " << node.getNameAsString() << "."
              << std::endl;
    std::cerr << "Text node: " << node.isTextNode() << std::endl
              << "Value: " << node.getContentBoth() << std::endl;
    return false;
  }
  //get child node
  if (!node.hasChild())
  {
    std::cerr << "Node <channel> has no child elements!";
    return false;
  }
  node = node.getChild();

  //initialize empty channel / feed
  feed = RSS091::Channel();

  while (true) //potentially endless loop
  {
    //Skip all non-element nodes (e.g. comment nodes).
    node.skipEmptyCommentAndTextSiblings();
    if (!node.isElementNode())
    {
      //No more element node means we can break out of the loop
      break;
    } //if

    const std::string nodeName = node.getNameAsString();
    bool errors = false;
    if (commonChannelElementFromNode(node, feed, errors))
    {
      if (errors)
      {
        //parsing failed
        return false;
      } //if
    } //if common channel element was parsed
    else if (nodeName == "item")
    {
      Item it = Item("", "", "");
      if (!itemFromNode(node, it))
      {
        std::cerr << "Could not parse RSS 0.91 item!" << std::endl;
        return false;
      }
      feed.addItem(it);
    } //if item
    else if (nodeName == "textinput")
    {
      if (!feed.textInput().empty())
      {
        std::cerr << "Feed already has a text input element!" << std::endl;
        return false;
      } //if text input element was already specified
      TextInput txIn;
      if (!textInputFromNode(node, txIn, true))
      {
        std::cerr << "Could not parse RSS 0.91 <textinput> element!" << std::endl;
        return false;
      }
      feed.setTextInput(std::move(txIn));
    } //if textInput
    else
    {
      std::cerr << "Found unexpected node name in channel: \"" << nodeName << "\"!"
                << std::endl;
      return false;
    }
    //Move to next sibling or break out of loop, if there are no more siblings.
    if (node.hasNextSibling())
      node = node.getNextSibling();
    else
      break;
  } //while
  //done
  return true;
}

} //namespace
