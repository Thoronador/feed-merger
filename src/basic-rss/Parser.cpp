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
      std::cout << "Parser::imageFromNode: Expected element node, but current"
                << " node is not an element node!" << std::endl;
      return false;
    }

    const std::string nodeName = child.getNameAsString();
    if (nodeName == "url")
    {
      if (!imageInfo.url().empty())
      {
        std::cout << "Image already has an URL!" << std::endl;
        return false;
      } //if URL was already specified
      imageInfo.setUrl(child.getContentBoth());
    }
    else if (nodeName == "title")
    {
      if (!imageInfo.title().empty())
      {
        std::cout << "Image already has a title!" << std::endl;
        return false;
      } //if title was already specified
      imageInfo.setTitle(child.getContentBoth());
    }
    else if (nodeName == "link")
    {
      if (!imageInfo.link().empty())
      {
        std::cout << "Image already has a link!" << std::endl;
        return false;
      } //if link was already specified
      imageInfo.setLink(child.getContentBoth());
    }
    else if (nodeName == "width")
    {
      if (imageInfo.width() > 0)
      {
        std::cout << "Image already has a width value!" << std::endl;
        return false;
      } //if width was already specified
      const std::string value = child.getContentBoth();
      int tempInt = -1;
      if (!stringToInt(value, tempInt))
      {
        std::cout << "Error: " << value << " is no integer value!" << std::endl;
        return false;
      }
      if (tempInt <= 0)
      {
        std::cout << "Width must be greater than zero, but current value is "
                  << tempInt << "!" << std::endl;
        return false;
      }
      imageInfo.setWidth(tempInt);
    }
    else if (nodeName == "height")
    {
      if (imageInfo.height() > 0)
      {
        std::cout << "Image already has a height value!" << std::endl;
        return false;
      } //if height was already specified
      const std::string value = child.getContentBoth();
      int tempInt = -1;
      if (!stringToInt(value, tempInt))
      {
        std::cout << "Error: " << value << " is no integer value!" << std::endl;
        return false;
      }
      if (tempInt <= 0)
      {
        std::cout << "Height must be greater than zero, but current value is "
                  << tempInt << "!" << std::endl;
        return false;
      }
      imageInfo.setHeight(tempInt);
    }
    else if (nodeName == "description")
    {
      if (!imageInfo.description().empty())
      {
        std::cout << "Image already has a description!" << std::endl;
        return false;
      } //if description was already specified
      imageInfo.setDescription(child.getContentBoth());
    }
    else
    {
      std::cout << "Found unexpected node name within image: \"" << nodeName
                << "\"!" << std::endl;
      return false;
    }
    child = child.getNextSibling();
  } //while
  //We are done here. Image should not be empty by now.
  return (!imageInfo.empty());
}

bool Parser::textInputFromNode(const XMLNode& textInputNode, TextInput& textInputInfo)
{
  if (!textInputNode.isElementNode() or (textInputNode.getNameAsString() != "textInput"))
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
      std::cout << "Parser::textInputFromNode: Expected element node, but current"
                << " node is not an element node!" << std::endl;
      return false;
    }

    const std::string nodeName = child.getNameAsString();
    if (nodeName == "title")
    {
      if (!textInputInfo.title().empty())
      {
        std::cout << "<textInput> already has a title!" << std::endl;
        return false;
      } //if title was already specified
      textInputInfo.setTitle(child.getContentBoth());
    }
    else if (nodeName == "description")
    {
      if (!textInputInfo.description().empty())
      {
        std::cout << "Text input box already has a description!" << std::endl;
        return false;
      } //if description was already specified
      textInputInfo.setDescription(child.getContentBoth());
    }
    else if (nodeName == "name")
    {
      if (!textInputInfo.name().empty())
      {
        std::cout << "Text input box already has a name!" << std::endl;
        return false;
      } //if name was already specified
      textInputInfo.setName(child.getContentBoth());
    }
    else if (nodeName == "link")
    {
      if (!textInputInfo.link().empty())
      {
        std::cout << "Text input box already has a link!" << std::endl;
        return false;
      } //if link was already specified
      textInputInfo.setLink(child.getContentBoth());
    }
    else
    {
      std::cout << "Found unexpected node name within textInput: \"" << nodeName
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
      std::cout << "Parser::skipHoursFromNode: Expected element node, but current"
                << " node is not an element node!" << std::endl;
      return false;
    }

    const std::string nodeName = child.getNameAsString();

    if (nodeName == "hour")
    {
      unsigned int hour = 25;
      if (!stringToUnsignedInt(child.getContentBoth(), hour))
      {
        std::cout << "Error while parsing <hour>'s content: "
                  << child.getContentBoth() << " is not an unsigned integer value!"
                  << std::endl;
        return false;
      }

      if (hour == 24)
        hour = 0;
      if (skipHoursInfo.find(hour) != skipHoursInfo.end())
      {
        std::cout << "Error: <skipHours> already contains hour " << hour
                  << "!" << std::endl;
        return false;
      }
      if (hour >= 24)
      {
        std::cout << "Error: <skipHours> only allows values up to 23, but encountered value is "
                  << hour << "!" << std::endl;
        return false;
      }
      skipHoursInfo.insert(hour);
    }
    else
    {
      std::cout << "Found unexpected node name within skipHours: \"" << nodeName
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
      std::cout << "Parser::skipDaysFromNode: Expected element node, but current"
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
        std::cout << "Error while parsing <day>'s content: " << strDay
                  << " is not an valid day of the week!" << std::endl;
        return false;
      }

      if (skipDaysInfo.find(day) != skipDaysInfo.end())
      {
        std::cout << "Error: <skipDays> already contains day " << strDay
                  << "!" << std::endl;
        return false;
      }
      skipDaysInfo.insert(day);
    }
    else
    {
      std::cout << "Found unexpected node name within skipDays: \"" << nodeName
                << "\"!" << std::endl;
      return false;
    }
    child = child.getNextSibling();
  } //while
  //We are done here. Set should not be empty by now.
  return (!skipDaysInfo.empty());
}

} //namespace
