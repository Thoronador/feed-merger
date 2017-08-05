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

namespace RSS20
{

bool Parser::itemFromNode(const XMLNode& itemNode, Item& theItem)
{
  if (!itemNode.isElementNode() or (itemNode.getNameAsString() != "item"))
    return false;

  theItem = Item("", "", "", "", std::set<Category>(), "", Enclosure(), GUID(),
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
      Category cat;
      if (!categoryFromNode(child, cat))
      {
        std::cout << "Could not parse RSS 2.0 <category> element!" << std::endl;
        return false;
      }
      if (theItem.category().find(cat) != theItem.category().end())
      {
        std::cout << "Item already has that category!" << std::endl;
        return false;
      } //if category was already specified
      theItem.addCategory(std::move(cat));
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
      if (!theItem.enclosure().empty())
      {
        std::cout << "Item already has an enclosure!" << std::endl;
        return false;
      }
      Enclosure encl;
      if (!enclosureFromNode(child, encl))
      {
        std::cout << "Could not parse RSS 2.0 <enclosure> element!" << std::endl;
        return false;
      }
      theItem.setEnclosure(std::move(encl));
    } //if enclosure
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
          permaLink = false;
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
    } //if GUID
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
      if (!theItem.source().empty())
      {
        std::cout << "Item's source was already set!" << std::endl;
        return false;
      } //if source was already specified
      Source src;
      if (!sourceFromNode(child, src))
      {
        std::cout << "Could not parse RSS 2.0 <source> element!" << std::endl;
        return false;
      }
      theItem.setSource(std::move(src));
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

bool Parser::cloudFromNode(const XMLNode& cloudNode, Cloud& cloudInfo)
{
  if (!cloudNode.isElementNode() or (cloudNode.getNameAsString() != "cloud"))
    return false;

  const auto attributes = cloudNode.getAttributes();
  if (attributes.size() != 5)
  {
    std::cout << "Cloud element should have exactly five attributes, but "
              << attributes.size() << " attributes were found instead."
              << std::endl;
    return false;
  } //if not five attributes

  //initialize element with empty values
  cloudInfo = Cloud();
  for (const auto& a : attributes)
  {
    const std::string attrName = a.first;
    if (attrName == "domain")
    {
      if (!cloudInfo.domain().empty())
      {
        std::cout << "Cloud element already has a domain!" << std::endl;
        return false;
      } //if domain was already specified
      cloudInfo.setDomain(a.second);
    } //if domain
    else if (attrName == "port")
    {
      if (cloudInfo.port() > 0)
      {
        std::cout << "Cloud element already has a port!" << std::endl;
        return false;
      } //if port was already specified
      int port = -1;
      if (!stringToInt(a.second, port))
      {
        std::cout << "Error while parsing <cloud>'s port: " << a.second
                  << " is not an integer value!" << std::endl;
        return false;
      }
      if ((port <= 0) or (port >= 65536))
      {
        std::cout << "Port of <cloud> element must be greater than zero and "
                  << "less than 65536." << std::endl;
        return false;
      }
      cloudInfo.setPort(port);
    } //if port
    else if (attrName == "path")
    {
      if (!cloudInfo.path().empty())
      {
        std::cout << "Cloud element already has a path!" << std::endl;
        return false;
      } //if path was already specified
      cloudInfo.setPath(a.second);
    } //if path
    else if (attrName == "registerProcedure")
    {
      if (!cloudInfo.registerProcedure().empty())
      {
        std::cout << "Cloud element already has a registerProcedure!" << std::endl;
        return false;
      } //if registerProcedure was already specified
      cloudInfo.setRegisterProcedure(a.second);
    } //if registerProcedure
    else if (attrName == "protocol")
    {
      if (!cloudInfo.protocol().empty())
      {
        std::cout << "Cloud element already has a protocol!" << std::endl;
        return false;
      } //if protocol was already specified
      cloudInfo.setProtocol(a.second);
    } //if protocol
    else
    {
      std::cout << "Error: found unknown attribute " << a.first
                << " in <cloud> element of RSS 2.0 channel!" << std::endl;
      return false;
    }
  } //for

  //Check, if all elements are set.
  if (cloudInfo.domain().empty() || cloudInfo.port() <= 0
      || cloudInfo.path().empty() || cloudInfo.registerProcedure().empty()
      || cloudInfo.protocol().empty())
  {
    std::cout << "Error: The <cloud> element of the RSS 2.0 channel does not "
              << "contain all the required information/attributes!" << std::endl;
      return false;
  }
  return true;
}

bool Parser::enclosureFromNode(const XMLNode& enclosureNode, Enclosure& enclosureInfo)
{
  if (!enclosureNode.isElementNode()
      or (enclosureNode.getNameAsString() != "enclosure"))
    return false;

  const auto attributes = enclosureNode.getAttributes();
  if (attributes.size() != 3)
  {
    std::cout << "Enclosure element should have exactly three attributes, but "
              << attributes.size() << " attributes were found instead."
              << std::endl;
    return false;
  } //if not three attributes

  //initialize element with empty values
  enclosureInfo = Enclosure();
  for (const auto& a : attributes)
  {
    const std::string attrName = a.first;
    if (attrName == "url")
    {
      if (!enclosureInfo.url().empty())
      {
        std::cout << "Enclosure element already has URL!" << std::endl;
        return false;
      } //if URL was already specified
      enclosureInfo.setUrl(a.second);
    } //if URL
    else if (attrName == "length")
    {
      if (enclosureInfo.length() > 0)
      {
        std::cout << "Enclosure element already has a length!" << std::endl;
        return false;
      } //if length was already specified
      unsigned int length = -1;
      if (!stringToUnsignedInt(a.second, length))
      {
        std::cout << "Error while parsing <enclosure>'s length: " << a.second
                  << " is not an integer value!" << std::endl;
        return false;
      }
      if (length <= 0)
      {
        std::cout << "Length value of <enclosure> element must be greater than zero." << std::endl;
        return false;
      }
      enclosureInfo.setLength(length);
    } //if port
    else if (attrName == "type")
    {
      if (!enclosureInfo.type().empty())
      {
        std::cout << "Enclosure element already has a type!" << std::endl;
        return false;
      } //if type was already specified
      enclosureInfo.setType(a.second);
    } //if path
    else
    {
      std::cout << "Error: found unknown attribute " << a.first
                << " in <enclosure> element of RSS 2.0 channel!" << std::endl;
      return false;
    }
  } //for

  //Check, if all elements are set.
  if (enclosureInfo.url().empty() || (enclosureInfo.length() <= 0)
      || enclosureInfo.type().empty())
  {
    std::cout << "Error: The <enclosure> element of the RSS 2.0 channel does not "
              << "contain all the required information/attributes!" << std::endl;
      return false;
  } //if
  return true;
}

bool Parser::sourceFromNode(const XMLNode& sourceNode, Source& sourceInfo)
{
  if (!sourceNode.isElementNode() or (sourceNode.getNameAsString() != "source"))
    return false;

  const auto attrs = sourceNode.getAttributes();
  if (attrs.size() != 1)
  {
    std::cout << "Error: Node <source> should have exactly one attribute!" << std::endl;
    return false;
  } //if
  if (attrs[0].first != "url")
  {
    std::cout << "Error: Node <source> should have a 'url' attribute!" << std::endl;
    return false;
  }
  sourceInfo = Source(sourceNode.getContentBoth(), attrs[0].second);
  if (sourceInfo.empty())
  {
    std::cout << "Error: <source> node is (partially) empty." << std::endl;
    return false;
  }
  return true;
}

bool Parser::categoryFromNode(const XMLNode& categoryNode, Category& categoryInfo)
{
  if (!categoryNode.isElementNode() or (categoryNode.getNameAsString() != "category"))
    return false;

  const auto attrs = categoryNode.getAttributes();
  if (attrs.size() > 1)
  {
    std::cout << "Error: Node <category> should have not more than one attribute!" << std::endl;
    return false;
  } //if
  categoryInfo = Category(categoryNode.getContentBoth(), "");
  if (!attrs.empty())
  {
    if (attrs[0].first != "domain")
    {
      std::cout << "Error: Node <category>'s attribute must be domain!" << std::endl;
      return false;
    } //if (inner)
    categoryInfo.setDomain(attrs[0].second);
  } //if
  return !categoryInfo.empty();
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
      Item it = Item("", "", "", "", std::set<Category>(), "", Enclosure(), GUID(),
                     0, Source());
      if (!itemFromNode(node, it))
      {
        std::cout << "Could not parse RSS 2.0 item!" << std::endl;
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
    } //if
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
    } //if
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
    } //if
    else if (nodeName == "category")
    {
      Category cat;
      if (!categoryFromNode(node, cat))
      {
        std::cout << "Could not parse RSS 2.0 <category> element!" << std::endl;
        return false;
      }
      if (feed.category().find(cat) != feed.category().end())
      {
        std::cout << "Feed already has that category!" << std::endl;
        return false;
      } //if category was already specified
      feed.addCategory(std::move(cat));
    } //if
    else if (nodeName == "generator")
    {
      if (!feed.generator().empty())
      {
        std::cout << "Feed generator was already set!" << std::endl;
        return false;
      } //if generator was already specified
      feed.setGenerator(node.getContentBoth());
    } //if
    else if (nodeName == "docs")
    {
      if (!feed.docs().empty())
      {
        std::cout << "Feed documentation URL was already set!" << std::endl;
        return false;
      } //if documentation URL was already specified
      feed.setDocs(node.getContentBoth());
    } //if docs
    else if (nodeName == "cloud")
    {
      if (!feed.cloud().empty())
      {
        std::cout << "Feed's cloud information was already set!" << std::endl;
        return false;
      } //if <cloud> was already specified
      Cloud cl;
      if (!cloudFromNode(node, cl))
      {
        std::cout << "Could not parse RSS 2.0 <cloud> element!" << std::endl;
        return false;
      }
      feed.setCloud(std::move(cl));
    } //if cloud
    else if (nodeName == "ttl")
    {
      if (feed.ttl() >= 0)
      {
        std::cout << "Feed's TTL was already set!" << std::endl;
        return false;
      } //if TTL was already specified
      const std::string ttlString = node.getContentBoth();

      int ttl = -1;
      if (!stringToInt(ttlString, ttl))
      {
        std::cout << "Error: \"" << ttlString << "\" is not an integer value,"
                  << " but TTL must be a (non-negative) integer." << std::endl;
        return false;
      }
      if (ttl < 0)
      {
        std::cout << "Feed's TTL must not be negative!" << std::endl;
        return false;
      }
      feed.setTtl(ttl);
    } //if ttl
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
        std::cout << "Could not parse RSS 2.0 <image> element!" << std::endl;
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
    else if (nodeName == "textInput")
    {
      if (!feed.textInput().empty())
      {
        std::cout << "Feed already has a text input element!" << std::endl;
        return false;
      } //if text input element was already specified
      TextInput txIn;
      if (!textInputFromNode(node, txIn))
      {
        std::cout << "Could not parse RSS 2.0 <textInput> element!" << std::endl;
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
        std::cout << "Could not parse RSS 2.0 <skipHours> element!" << std::endl;
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
        std::cout << "Could not parse RSS 2.0 <skipDays> element!" << std::endl;
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
  return true;
}

} //namespace
