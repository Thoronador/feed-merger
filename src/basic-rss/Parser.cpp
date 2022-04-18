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

namespace BasicRSS
{

bool Parser::imageFromNode(const XMLNode& imageNode, Image& imageInfo)
{
  if (!imageNode.isElementNode() or (imageNode.getNameAsString() != "image"))
    return false;

  if (!imageNode.hasChild())
    return false;

  XMLNode child = imageNode.getChild();

  imageInfo = Image();

  while (child.hasNextSibling())
  {
    child.skipEmptyCommentAndTextSiblings();

    if (!child.isElementNode())
    {
      std::cerr << "Parser::imageFromNode: Expected element node, but current"
                << " node is not an element node!" << std::endl;
      return false;
    }

    const std::string nodeName = child.getNameAsString();
    if (nodeName == "url")
    {
      if (!imageInfo.url().empty())
      {
        std::cerr << "Image already has an URL!" << std::endl;
        return false;
      } //if URL was already specified
      imageInfo.setUrl(child.getContentBoth());
    }
    else if (nodeName == "title")
    {
      if (!imageInfo.title().empty())
      {
        std::cerr << "Image already has a title!" << std::endl;
        return false;
      } //if title was already specified
      imageInfo.setTitle(child.getContentBoth());
    }
    else if (nodeName == "link")
    {
      if (!imageInfo.link().empty())
      {
        std::cerr << "Image already has a link!" << std::endl;
        return false;
      } //if link was already specified
      imageInfo.setLink(child.getContentBoth());
    }
    else if (nodeName == "width")
    {
      if (imageInfo.width().has_value())
      {
        std::cerr << "Image already has a width value!" << std::endl;
        return false;
      } //if width was already specified
      const std::string value = child.getContentBoth();
      int tempInt = -1;
      if (!stringToInt(value, tempInt))
      {
        std::cerr << "Error: " << value << " is no integer value!" << std::endl;
        return false;
      }
      if (tempInt <= 0)
      {
        std::cerr << "Width must be greater than zero, but current value is "
                  << tempInt << "!" << std::endl;
        return false;
      }
      imageInfo.setWidth(tempInt);
    }
    else if (nodeName == "height")
    {
      if (imageInfo.height().has_value())
      {
        std::cerr << "Image already has a height value!" << std::endl;
        return false;
      } //if height was already specified
      const std::string value = child.getContentBoth();
      int tempInt = -1;
      if (!stringToInt(value, tempInt))
      {
        std::cerr << "Error: " << value << " is no integer value!" << std::endl;
        return false;
      }
      if (tempInt <= 0)
      {
        std::cerr << "Height must be greater than zero, but current value is "
                  << tempInt << "!" << std::endl;
        return false;
      }
      imageInfo.setHeight(tempInt);
    }
    else if (nodeName == "description")
    {
      if (!imageInfo.description().empty())
      {
        std::cerr << "Image already has a description!" << std::endl;
        return false;
      } //if description was already specified
      imageInfo.setDescription(child.getContentBoth());
    }
    else
    {
      std::cerr << "Found unexpected node name within image: \"" << nodeName
                << "\"!" << std::endl;
      return false;
    }
    child = child.getNextSibling();
  } //while
  //We are done here. Image should not be empty by now.
  return (!imageInfo.empty());
}

bool Parser::textInputFromNode(const XMLNode& textInputNode, TextInput& textInputInfo, const bool rss091)
{
  if (!textInputNode.isElementNode()
      //upper-case i in element name for RSS 2.0
      || ((textInputNode.getNameAsString() != "textInput") && !rss091)
      //lower-case i in element name for RSS 2.0
      || ((textInputNode.getNameAsString() != "textinput") && rss091))
    return false;

  if (!textInputNode.hasChild())
    return false;

  XMLNode child = textInputNode.getChild();

  textInputInfo = TextInput();

  while (child.hasNextSibling())
  {
    child.skipEmptyCommentAndTextSiblings();

    if (!child.isElementNode())
    {
      std::cerr << "Parser::textInputFromNode: Expected element node, but current"
                << " node is not an element node!" << std::endl;
      return false;
    }

    const std::string nodeName = child.getNameAsString();
    if (nodeName == "title")
    {
      if (!textInputInfo.title().empty())
      {
        std::cerr << "<textInput> already has a title!" << std::endl;
        return false;
      } //if title was already specified
      textInputInfo.setTitle(child.getContentBoth());
    }
    else if (nodeName == "description")
    {
      if (!textInputInfo.description().empty())
      {
        std::cerr << "Text input box already has a description!" << std::endl;
        return false;
      } //if description was already specified
      textInputInfo.setDescription(child.getContentBoth());
    }
    else if (nodeName == "name")
    {
      if (!textInputInfo.name().empty())
      {
        std::cerr << "Text input box already has a name!" << std::endl;
        return false;
      } //if name was already specified
      textInputInfo.setName(child.getContentBoth());
    }
    else if (nodeName == "link")
    {
      if (!textInputInfo.link().empty())
      {
        std::cerr << "Text input box already has a link!" << std::endl;
        return false;
      } //if link was already specified
      textInputInfo.setLink(child.getContentBoth());
    }
    else
    {
      std::cerr << "Found unexpected node name within textInput: \"" << nodeName
                << "\"!" << std::endl;
      return false;
    }
    child = child.getNextSibling();
  } //while
  //We are done here. Text input box should not be empty by now.
  return (!textInputInfo.empty());
}

bool Parser::skipHoursFromNode(const XMLNode& skipHoursNode, std::set<unsigned int>& skipHoursInfo)
{
  if (!skipHoursNode.isElementNode() or (skipHoursNode.getNameAsString() != "skipHours"))
    return false;

  if (!skipHoursNode.hasChild())
    return false;

  XMLNode child = skipHoursNode.getChild();

  skipHoursInfo = std::set<unsigned int>();

  while (child.hasNextSibling())
  {
    child.skipEmptyCommentAndTextSiblings();

    if (!child.isElementNode())
    {
      std::cerr << "Parser::skipHoursFromNode: Expected element node, but current"
                << " node is not an element node!" << std::endl;
      return false;
    }

    const std::string nodeName = child.getNameAsString();

    if (nodeName == "hour")
    {
      unsigned int hour = 25;
      if (!stringToUnsignedInt(child.getContentBoth(), hour))
      {
        std::cerr << "Error while parsing <hour>'s content: "
                  << child.getContentBoth() << " is not an unsigned integer value!"
                  << std::endl;
        return false;
      }

      if (hour == 24)
        hour = 0;
      if (skipHoursInfo.find(hour) != skipHoursInfo.end())
      {
        std::cerr << "Error: <skipHours> already contains hour " << hour
                  << "!" << std::endl;
        return false;
      }
      if (hour >= 24)
      {
        std::cerr << "Error: <skipHours> only allows values up to 23, but encountered value is "
                  << hour << "!" << std::endl;
        return false;
      }
      skipHoursInfo.insert(hour);
    }
    else
    {
      std::cerr << "Found unexpected node name within skipHours: \"" << nodeName
                << "\"!" << std::endl;
      return false;
    }
    child = child.getNextSibling();
  } //while
  //We are done here. Set should not be empty by now.
  return (!skipHoursInfo.empty());
}

bool Parser::skipDaysFromNode(const XMLNode& skipDaysNode, std::set<Days>& skipDaysInfo)
{
  if (!skipDaysNode.isElementNode() or (skipDaysNode.getNameAsString() != "skipDays"))
    return false;

  if (!skipDaysNode.hasChild())
    return false;

  XMLNode child = skipDaysNode.getChild();

  skipDaysInfo = std::set<Days>();

  while (child.hasNextSibling())
  {
    child.skipEmptyCommentAndTextSiblings();

    if (!child.isElementNode())
    {
      std::cerr << "Parser::skipDaysFromNode: Expected element node, but current"
                << " node is not an element node!" << std::endl;
      return false;
    }

    const std::string nodeName = child.getNameAsString();

    if (nodeName == "day")
    {
      Days day = Days::Monday;
      const std::string strDay = child.getContentBoth();
      if (strDay == "Monday")
        day = Days::Monday;
      else if (strDay == "Tuesday")
        day = Days::Tuesday;
      else if (strDay == "Wednesday")
        day = Days::Wednesday;
      else if (strDay == "Thursday")
        day = Days::Thursday;
      else if (strDay == "Friday")
        day = Days::Friday;
      else if (strDay == "Saturday")
        day = Days::Saturday;
      else if (strDay == "Sunday")
        day = Days::Sunday;
      else
      {
        std::cerr << "Error while parsing <day>'s content: " << strDay
                  << " is not an valid day of the week!" << std::endl;
        return false;
      }

      if (skipDaysInfo.find(day) != skipDaysInfo.end())
      {
        std::cerr << "Error: <skipDays> already contains day " << strDay
                  << "!" << std::endl;
        return false;
      }
      skipDaysInfo.insert(day);
    }
    else
    {
      std::cerr << "Found unexpected node name within skipDays: \"" << nodeName
                << "\"!" << std::endl;
      return false;
    }
    child = child.getNextSibling();
  } //while
  //We are done here. Set should not be empty by now.
  return (!skipDaysInfo.empty());
}

bool Parser::commonChannelElementFromNode(const XMLNode& node, Channel& feed, bool& errorFlag)
{
  errorFlag = false;
  const std::string nodeName = node.getNameAsString();
  if (nodeName == "title")
  {
    if (!feed.title().empty())
    {
      std::cerr << "Feed already has a title!" << std::endl;
      errorFlag = true;
      return true;
    } //if title was already specified
    feed.setTitle(node.getContentBoth());
  } //if title
  else if (nodeName == "link")
  {
    if (!feed.link().empty())
    {
      std::cerr << "Feed already has a link!" << std::endl;
      errorFlag = true;
      return true;
    } //if link was already specified
    feed.setLink(node.getContentBoth());
  } //if link
  else if (nodeName == "description")
  {
    if (!feed.description().empty())
    {
      std::cerr << "Feed already has a description!" << std::endl;
      errorFlag = true;
      return true;
    } //if description was already specified
    feed.setDescription(node.getContentBoth());
  } //if description
  else if (nodeName == "language")
  {
    if (!feed.language().empty())
    {
      std::cerr << "Feed already has a language!" << std::endl;
      errorFlag = true;
      return true;
    } //if language was already specified
    feed.setLanguage(node.getContentBoth());
  } //if language
  else if (nodeName == "copyright")
  {
    if (!feed.copyright().empty())
    {
      std::cerr << "Feed already has a copyright notice!" << std::endl;
      errorFlag = true;
      return true;
    } //if copyright notice was already specified
    feed.setCopyright(node.getContentBoth());
  } //if copyright
  else if (nodeName == "managingEditor")
  {
    if (!feed.managingEditor().empty())
    {
      std::cerr << "Feed already has an address for the managing editor!" << std::endl;
      errorFlag = true;
      return true;
    } //if address was already specified
    feed.setManagingEditor(node.getContentBoth());
  } //if
  else if (nodeName == "webMaster")
  {
    if (!feed.webMaster().empty())
    {
      std::cerr << "Feed already has an address for the webmaster!" << std::endl;
      errorFlag = true;
      return true;
    } //if address was already specified
    feed.setWebMaster(node.getContentBoth());
  } //if webMaster
  else if (nodeName == "pubDate")
  {
    if (feed.pubDate() != 0)
    {
      std::cerr << "Feed already has a publication date!" << std::endl;
      errorFlag = true;
      return true;
    } //if pubDate was already specified
    std::time_t thePubDate = 0;
    if (!rfc822DateTimeToTimeT(node.getContentBoth(), thePubDate))
    {
      std::cerr << "Could not parse publication date \""
                << node.getContentBoth() << "\"!" <<std::endl;
      errorFlag = true;
      return true;
    }
    feed.setPubDate(thePubDate);
  } //if pubDate
  else if (nodeName == "lastBuildDate")
  {
    if (feed.lastBuildDate() != 0)
    {
      std::cerr << "Feed already has a last change date!" << std::endl;
      errorFlag = true;
      return true;
    } //if lastBuildDate was already specified
    std::time_t theLastBuildDate = 0;
    if (!rfc822DateTimeToTimeT(node.getContentBoth(), theLastBuildDate))
    {
      std::cerr << "Could not parse last change date \""
                << node.getContentBoth() << "\"!" << std::endl;
      errorFlag = true;
      return true;
    }
    feed.setLastBuildDate(theLastBuildDate);
  } //if lastBuildDate
  else if (nodeName == "docs")
  {
    if (!feed.docs().empty())
    {
      std::cerr << "Feed documentation URL was already set!" << std::endl;
      errorFlag = true;
      return true;
    } //if documentation URL was already specified
    feed.setDocs(node.getContentBoth());
  } //if docs
  else if (nodeName == "image")
  {
    if (!feed.image().empty())
    {
      std::cerr << "Feed's image was already set!" << std::endl;
      errorFlag = true;
      return true;
    } //if image was already specified
    Image img;
    if (!imageFromNode(node, img))
    {
      std::cerr << "Could not parse RSS <image> element!" << std::endl;
      errorFlag = true;
      return true;
    }
    feed.setImage(std::move(img));
  } //if image
  else if (nodeName == "rating")
  {
    if (!feed.rating().empty())
    {
      std::cerr << "Feed already has a rating!" << std::endl;
      errorFlag = true;
      return true;
    } //if rating was already specified
    feed.setRating(node.getContentBoth());
  } //if rating
  else if (nodeName == "skipHours")
  {
    if (!feed.skipHours().empty())
    {
      std::cerr << "Feed already has skipHours set!" << std::endl;
      errorFlag = true;
      return true;
    } //if skipHours was already specified
    std::set<unsigned int> skipH;
    if (!skipHoursFromNode(node, skipH))
    {
      std::cerr << "Could not parse RSS <skipHours> element!" << std::endl;
      errorFlag = true;
      return true;
    }
    feed.setSkipHours(std::move(skipH));
  } //if skipHours
  else if (nodeName == "skipDays")
  {
    if (!feed.skipDays().empty())
    {
      std::cerr << "Feed already has skipDays set!" << std::endl;
      errorFlag = true;
      return true;
    } //if skipDays was already specified
    std::set<BasicRSS::Days> skipD;
    if (!skipDaysFromNode(node, skipD))
    {
      std::cerr << "Could not parse RSS <skipDays> element!" << std::endl;
      errorFlag = true;
      return true;
    }
    feed.setSkipDays(std::move(skipD));
  } //if skipDays
  else
  {
    //no matching element found
    return false;
  }
  //We parsed some kind of XML node, so return true.
  return true;
}

} //namespace
