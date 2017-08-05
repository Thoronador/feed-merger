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
      std::cout << "Parser::itemFromNode: Expected element node, but current"
                << " XML node is not an element node!" << std::endl;
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
  if (node.getNameAsString() != "rss")
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
  if (node.getFirstAttributeValue() != "0.91")
  {
    std::cout << "Version of feed is not 0.91, but \""
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
      Item it = Item("", "", "");
      if (!itemFromNode(node, it))
      {
        std::cout << "Could not parse RSS 0.91 item!" << std::endl;
        return false;
      }
      feed.addItem(it);
    } //if item
    else if (nodeName == "language")
    {
      if (!feed.language().empty())
      {
        std::cout << "Feed already has a language!" << std::endl;
        return false;
      } //if language was already specified
      feed.setLanguage(node.getContentBoth());
    } //if
    else if (nodeName == "copyright")
    {
      if (!feed.copyright().empty())
      {
        std::cout << "Feed already has a copyright notice!" << std::endl;
        return false;
      } //if copyright notice was already specified
      feed.setCopyright(node.getContentBoth());
    } //if
    else if (nodeName == "managingEditor")
    {
      if (!feed.managingEditor().empty())
      {
        std::cout << "Feed already has an address for the managing editor!" << std::endl;
        return false;
      } //if address was already specified
      feed.setManagingEditor(node.getContentBoth());
    } //if
    else if (nodeName == "webMaster")
    {
      if (!feed.webMaster().empty())
      {
        std::cout << "Feed already has an address for the webmaster!" << std::endl;
        return false;
      } //if address was already specified
      feed.setWebMaster(node.getContentBoth());
    } //if webMaster
    else if (nodeName == "pubDate")
    {
      if (feed.pubDate() != 0)
      {
        std::cout << "Feed already has a publication date!" << std::endl;
        return false;
      } //if pubDate was already specified
      std::time_t thePubDate = 0;
      if (!rfc822DateTimeToTimeT(node.getContentBoth(), thePubDate))
      {
        std::cout << "Could not parse publication date \""
                  << node.getContentBoth() << "\"!" <<std::endl;
        return false;
      }
      feed.setPubDate(thePubDate);
    } //if pubDate
    else if (nodeName == "lastBuildDate")
    {
      if (feed.lastBuildDate() != 0)
      {
        std::cout << "Feed already has a last change date!" << std::endl;
        return false;
      } //if lastBuildDate was already specified
      std::time_t theLastBuildDate = 0;
      if (!rfc822DateTimeToTimeT(node.getContentBoth(), theLastBuildDate))
      {
        std::cout << "Could not parse last change date \""
                  << node.getContentBoth() << "\"!" <<std::endl;
        return false;
      }
      feed.setLastBuildDate(theLastBuildDate);
    } //if lastBuildDate
    else if (nodeName == "docs")
    {
      if (!feed.docs().empty())
      {
        std::cout << "Feed documentation URL was already set!" << std::endl;
        return false;
      } //if documentation URL was already specified
      feed.setDocs(node.getContentBoth());
    } //if docs
    else if (nodeName == "image")
    {
      if (!feed.image().empty())
      {
        std::cout << "Feed's image was already set!" << std::endl;
        return false;
      } //if image was already specified
      Image img;
      if (!imageFromNode(node, img))
      {
        std::cout << "Could not parse RSS 0.91 <image> element!" << std::endl;
        return false;
      }
      feed.setImage(std::move(img));
    } //if image
    else if (nodeName == "rating")
    {
      if (!feed.rating().empty())
      {
        std::cout << "Feed already has a rating!" << std::endl;
        return false;
      } //if rating was already specified
      feed.setRating(node.getContentBoth());
    } //if rating
    else if (nodeName == "textinput")
    {
      if (!feed.textInput().empty())
      {
        std::cout << "Feed already has a text input element!" << std::endl;
        return false;
      } //if text input element was already specified
      TextInput txIn;
      if (!textInputFromNode(node, txIn, true))
      {
        std::cout << "Could not parse RSS 0.91 <textinput> element!" << std::endl;
        return false;
      }
      feed.setTextInput(std::move(txIn));
    } //if textInput
    else if (nodeName == "skipHours")
    {
      if (!feed.skipHours().empty())
      {
        std::cout << "Feed already has skipHours set!" << std::endl;
        return false;
      } //if skipHours was already specified
      std::set<unsigned int> skipH;
      if (!skipHoursFromNode(node, skipH))
      {
        std::cout << "Could not parse RSS 0.91 <skipHours> element!" << std::endl;
        return false;
      }
      feed.setSkipHours(std::move(skipH));
    } //if skipHours
    else if (nodeName == "skipDays")
    {
      if (!feed.skipDays().empty())
      {
        std::cout << "Feed already has skipDays set!" << std::endl;
        return false;
      } //if skipDays was already specified
      std::set<BasicRSS::Days> skipD;
      if (!skipDaysFromNode(node, skipD))
      {
        std::cout << "Could not parse RSS 0.91 <skipDays> element!" << std::endl;
        return false;
      }
      feed.setSkipDays(std::move(skipD));
    } //if skipDays
    else
    {
      std::cout << "Found unexpected node name in channel: \"" << nodeName << "\"!"
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
