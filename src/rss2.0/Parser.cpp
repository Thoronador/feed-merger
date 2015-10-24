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
#include "../rfc822/Date.hpp"
#include "../xml/XMLDocument.hpp"

namespace RSS20
{

bool Parser::itemFromNode(const XMLNode& itemNode, Item& theItem)
{
  if (!itemNode.isElementNode() or (itemNode.getNameAsString() != "item"))
    return false;

  theItem = Item("", "", "", "", Category(), "", Enclosure(), GUID(),
                 0, Source());

  if (!itemNode.hasChild())
    return false;

  XMLNode child = itemNode.getChild();

  while (child.hasNextSibling())
  {
    child.skipEmptyCommentAndTextSiblings();

    if (!child.isElementNode())
    {
      std::cout << "Parser::itemFromNode: Expected element node, but current"
                << " node is not an element node!" << std::endl;
      return false;
    }

    const std::string nodeName = child.getNameAsString();

    if (nodeName == "title")
    {
      if (!theItem.title().empty())
      {
        std::cout << "Item already has a title!" << std::endl;
        return false;
      } //if title was already specified
      theItem.setTitle(child.getContentBoth());
    }
    else if (nodeName == "link")
    {
      if (!theItem.link().empty())
      {
        std::cout << "Item already has a link!" << std::endl;
        return false;
      } //if link was already specified
      theItem.setLink(child.getContentBoth());
    }
    else if (nodeName == "description")
    {
      if (!theItem.description().empty())
      {
        std::cout << "Item already has a description!" << std::endl;
        return false;
      } //if description was already specified
      theItem.setDescription(child.getContentBoth());
    }
    else if (nodeName == "author")
    {
      if (!theItem.author().empty())
      {
        std::cout << "Item already has a author!" << std::endl;
        return false;
      } //if author was already specified
      theItem.setAuthor(child.getContentBoth());
    }
    else if (nodeName == "category")
    {
      #warning Not implemented yet!
      std::cout << "Category parsing is not implemented yet!" << std::endl;
      return false;
    }
    else if (nodeName == "comments")
    {
      if (!theItem.comments().empty())
      {
        std::cout << "Item already has a comment URL!" << std::endl;
        return false;
      } //if comments was already specified
      theItem.setComments(child.getContentBoth());
    }
    else if (nodeName == "enclosure")
    {
      #warning Not implemented yet!
      std::cout << "Enclosure parsing is not implemented yet!" << std::endl;
      return false;
    }
    else if (nodeName == "guid")
    {
      if (!theItem.guid().empty())
      {
        std::cout << "Item already has a GUID!" << std::endl;
        return false;
      } //if GUID was already specified
      const std::string plainGUID = child.getContentBoth();
      bool permaLink = false;
      if (!child.hasAttribute())
        permaLink = true;
      else
      {
        //The only allowed attribute for <guid> is "isPermaLink".
        if (child.getFirstAttributeName() != "isPermaLink")
        {
          std::cout << "Error: <guid> may not have other attributes than "
                    << "'isPermaLink', but " << child.getFirstAttributeName()
                    << " was found!" << std::endl;
          return false;
        } //if attribute is not "isPermaLink"
        const std::string isPermaLink = child.getFirstAttributeValue();
        if (isPermaLink == "true")
          permaLink = true;
        else if (isPermaLink == "false")
          permaLink == false;
        else
        {
          std::cout << "Error: Value of attribute isPermaLink in <guid> has "
                    << "to be either \"true\" or \"false\", but it is \""
                    << isPermaLink << "\" instead." << std::endl;
          return false;
        } //else
      } //if attribute is present
      //set GUID
      theItem.setGUID(GUID(plainGUID, permaLink));
    }
    else if (nodeName == "pubDate")
    {
      if (theItem.pubDate() != 0)
      {
        std::cout << "Item already has a publication date!" << std::endl;
        return false;
      } //if pubDate was already specified
      std::time_t thePubDate = 0;
      if (!rfc822DateTimeToTimeT(child.getContentBoth(), thePubDate))
      {
        std::cout << "Could not parse publication date \""
                  << child.getContentBoth() << "\"!" <<std::endl;
        return false;
      }
      theItem.setPubDate(thePubDate);
    }
    else if (nodeName == "source")
    {
      #warning Not implemented yet!
      std::cout << "Source parsing is not implemented yet!" << std::endl;
      return false;
    }
    else
    {
      std::cout << "Found unexpected node name within item: \"" << nodeName
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
  node.skipEmptyCommentAndTextSiblings();

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
      if (!feed.title().empty())
      {
        std::cout << "Feed already has a title!" << std::endl;
        return false;
      } //if title was already specified
      feed.setTitle(node.getContentBoth());
    } //if title
    else if (nodeName == "link")
    {
      if (!feed.link().empty())
      {
        std::cout << "Feed already has a link!" << std::endl;
        return false;
      } //if link was already specified
      feed.setLink(node.getContentBoth());
    } //if link
    else if (nodeName == "description")
    {
      if (!feed.description().empty())
      {
        std::cout << "Feed already has a description!" << std::endl;
        return false;
      } //if description was already specified
      feed.setDescription(node.getContentBoth());
    } //if description
    else if (nodeName == "item")
    {
      Item it = Item("", "", "", "", Category(), "", Enclosure(), GUID(),
                     0, Source());
      if (!itemFromNode(node, it))
      {
        std::cout << "Could not parse RSS 2.0 item!" << std::endl;
        return false;
      }
      feed.addItem(it);
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
