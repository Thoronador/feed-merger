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

#include "Writer.hpp"
#include <iostream>
#include <libxml/tree.h>
#include <libxml/xmlwriter.h>
#include "../rfc822/Date.hpp"
#include "../StringFunctions.hpp"

namespace RSS20
{

bool Writer::toFile(const Channel& feed, const std::string& fileName)
{
  xmlDocPtr document = nullptr;
  xmlTextWriterPtr writer = nullptr;

  /* Create a new XmlWriter for DOM, with no compression. */
  writer = xmlNewTextWriterDoc(&document, 0);
  if (nullptr == writer)
  {
    std::cout << "Error: Could not create XML writer!" << std::endl;
    if (nullptr != document)
      xmlFreeDoc(document);
    return false;
  } //if

  //start XML document - version 1.0, UTF-8 encoding
  int ret = xmlTextWriterStartDocument(writer, "1.0", "UTF-8", NULL);
  if (ret < 0)
  {
    std::cout << "Error: Could not start XML document!" << std::endl;
    xmlFreeTextWriter(writer);
    if (nullptr != document)
      xmlFreeDoc(document);
    return false;
  }

  //start rss element
  ret = xmlTextWriterStartElement(writer, reinterpret_cast<const xmlChar*>("rss"));
  if (ret < 0)
  {
    std::cout << "Error: Could not write <rss> element!" << std::endl;
    xmlFreeTextWriter(writer);
    if (nullptr != document)
      xmlFreeDoc(document);
    return false;
  }

  //write attribute version="2.0"
  ret = xmlTextWriterWriteAttribute(writer, reinterpret_cast<const xmlChar*>("version"), reinterpret_cast<const xmlChar*>("2.0"));
  if (ret < 0)
  {
    std::cout << "Error: Could not add version attribute to <rss> element!" << std::endl;
    xmlFreeTextWriter(writer);
    if (nullptr != document)
      xmlFreeDoc(document);
    return false;
  }

  //write <channel>
  ret = xmlTextWriterStartElement(writer, reinterpret_cast<const xmlChar*>("channel"));
  if (ret < 0)
  {
    std::cout << "Error: Could not write <channel> element!" << std::endl;
    xmlFreeTextWriter(writer);
    if (nullptr != document)
      xmlFreeDoc(document);
    return false;
  }

  //write <title>
  ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("title"),
            reinterpret_cast<const xmlChar*>(feed.title().c_str()));
  if (ret < 0)
  {
    std::cout << "Error: Could not write <title> element!" << std::endl;
    xmlFreeTextWriter(writer);
    if (nullptr != document)
      xmlFreeDoc(document);
    return false;
  }

  //write <link>
  ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("link"),
            reinterpret_cast<const xmlChar*>(feed.link().c_str()));
  if (ret < 0)
  {
    std::cout << "Error: Could not write <link> element!" << std::endl;
    xmlFreeTextWriter(writer);
    if (nullptr != document)
      xmlFreeDoc(document);
    return false;
  }

  //write <description>
  ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("description"),
            reinterpret_cast<const xmlChar*>(feed.description().c_str()));
  if (ret < 0)
  {
    std::cout << "Error: Could not write <description> element!" << std::endl;
    xmlFreeTextWriter(writer);
    if (nullptr != document)
      xmlFreeDoc(document);
    return false;
  }


  /* ********************* */
  /* ********************* */
  #warning TODO: write items!
  /* ********************* */
  /* ********************* */


  //write <language>
  if (!feed.language().empty())
  {
    ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("language"),
              reinterpret_cast<const xmlChar*>(feed.language().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write <language> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
  } //if language

  //write <copyright>
  if (!feed.copyright().empty())
  {
    ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("copyright"),
              reinterpret_cast<const xmlChar*>(feed.copyright().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write <copyright> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
  } //if copyright

  //write <managingEditor>
  if (!feed.managingEditor().empty())
  {
    ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("managingEditor"),
              reinterpret_cast<const xmlChar*>(feed.managingEditor().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write <managingEditor> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
  } //if managingEditor

  //write <webMaster>
  if (!feed.webMaster().empty())
  {
    ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("webMaster"),
              reinterpret_cast<const xmlChar*>(feed.webMaster().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write <webMaster> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
  } //if webMaster

  //write <pubDate>
  if (feed.pubDate() != static_cast<std::time_t>(0))
  {
    std::string pubDate;
    if (!timeToRFC822String(feed.pubDate(), pubDate))
    {
      std::cout << "Error: Could not convert pubDate (time_t) to string!" << std::endl;
      return false;
    } //if conversion failed
    ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("pubDate"),
              reinterpret_cast<const xmlChar*>(pubDate.c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write <pubDate> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
  } //if pubDate

  //write <lastBuildDate>
  if (feed.lastBuildDate() != static_cast<std::time_t>(0))
  {
    std::string lastBuildDate;
    if (!timeToRFC822String(feed.lastBuildDate(), lastBuildDate))
    {
      std::cout << "Error: Could not convert lastBuildDate (time_t) to string!" << std::endl;
      return false;
    } //if conversion failed
    ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("lastBuildDate"),
              reinterpret_cast<const xmlChar*>(lastBuildDate.c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write <lastBuildDate> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
  } //if lastBuildDate

  //write <category>
  if (!feed.category().empty())
  {
    ret = xmlTextWriterStartElement(writer, reinterpret_cast<const xmlChar*>("category"));
    if (ret < 0)
    {
      std::cout << "Error: Could not start <category> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
    //attribute domain
    if (!feed.category().domain().empty())
    {
      ret = xmlTextWriterWriteAttribute(writer, reinterpret_cast<const xmlChar*>("domain"),
                reinterpret_cast<const xmlChar*>(feed.category().domain().c_str()));
      if (ret < 0)
      {
        std::cout << "Error: Could not write domain attribute of <category> element!" << std::endl;
        xmlFreeTextWriter(writer);
        if (nullptr != document)
          xmlFreeDoc(document);
        return false;
      }
    } //if domain attribute is present

    //write category string
    ret = xmlTextWriterWriteString(writer,
              reinterpret_cast<const xmlChar*>(feed.category().get().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write content of <category> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
    //close category element
    ret = xmlTextWriterEndElement(writer);
    if (ret < 0)
    {
      std::cout << "Error: Could not end <category> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    } //if
  } //if category

  //write <generator>
  if (!feed.generator().empty())
  {
    ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("generator"),
              reinterpret_cast<const xmlChar*>(feed.generator().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write <generator> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
  } //if generator

  //write <docs>
  if (!feed.docs().empty())
  {
    ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("docs"),
              reinterpret_cast<const xmlChar*>(feed.docs().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write <docs> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
  } //if docs

  //write <cloud>
  if (!feed.cloud().empty())
  {
    //open cloud tag
    ret = xmlTextWriterStartElement(writer, reinterpret_cast<const xmlChar*>("cloud"));
    if (ret < 0)
    {
      std::cout << "Error: Could not start <cloud> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
    //attribute domain
    ret = xmlTextWriterWriteAttribute(writer, reinterpret_cast<const xmlChar*>("domain"),
              reinterpret_cast<const xmlChar*>(feed.cloud().domain().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write domain attribute of <cloud> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
    //attribute port
    ret = xmlTextWriterWriteAttribute(writer, reinterpret_cast<const xmlChar*>("port"),
              reinterpret_cast<const xmlChar*>(intToString(feed.cloud().port()).c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write port attribute of <cloud> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
    //attribute path
    ret = xmlTextWriterWriteAttribute(writer, reinterpret_cast<const xmlChar*>("path"),
              reinterpret_cast<const xmlChar*>(feed.cloud().path().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write path attribute of <cloud> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
    //attribute registerProcedure
    ret = xmlTextWriterWriteAttribute(writer, reinterpret_cast<const xmlChar*>("registerProcedure"),
              reinterpret_cast<const xmlChar*>(feed.cloud().registerProcedure().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write registerProcedure attribute of <cloud> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
    //attribute protocol
    ret = xmlTextWriterWriteAttribute(writer, reinterpret_cast<const xmlChar*>("protocol"),
              reinterpret_cast<const xmlChar*>(feed.cloud().protocol().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write protocol attribute of <cloud> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
    //close cloud element
    ret = xmlTextWriterEndElement(writer);
    if (ret < 0)
    {
      std::cout << "Error: Could not end <cloud> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
  } //if cloud

  //write <ttl>
  if (feed.ttl() > 0)
  {
    ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("ttl"),
              reinterpret_cast<const xmlChar*>(intToString(feed.ttl()).c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write <ttl> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
  } //if ttl

  //write <image>
  if (!feed.image().empty())
  {
    //open image tag
    ret = xmlTextWriterStartElement(writer, reinterpret_cast<const xmlChar*>("image"));
    if (ret < 0)
    {
      std::cout << "Error: Could not start <image> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
    /* required elements: url, title, link, so no check for emptiness */
    //write <url>
    ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("url"),
              reinterpret_cast<const xmlChar*>(feed.image().url().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write <url> element of <image>!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
    //write <title>
    ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("title"),
              reinterpret_cast<const xmlChar*>(feed.image().title().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write <title> element of <image>!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
    //write <link>
    ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("link"),
              reinterpret_cast<const xmlChar*>(feed.image().link().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write <title> element of <image>!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
    //write <width>
    if (feed.image().width() > 0)
    {
      //write <width>
      ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("width"),
                reinterpret_cast<const xmlChar*>(intToString(feed.image().width()).c_str()));
      if (ret < 0)
      {
        std::cout << "Error: Could not write <width> element of <image>!" << std::endl;
        xmlFreeTextWriter(writer);
        if (nullptr != document)
          xmlFreeDoc(document);
        return false;
      }
    } //if width
    //write <height>
    if (feed.image().height() > 0)
    {
      //write <width>
      ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("height"),
                reinterpret_cast<const xmlChar*>(intToString(feed.image().height()).c_str()));
      if (ret < 0)
      {
        std::cout << "Error: Could not write <height> element of <image>!" << std::endl;
        xmlFreeTextWriter(writer);
        if (nullptr != document)
          xmlFreeDoc(document);
        return false;
      }
    } //if height
    //write <description>
    if (!feed.image().description().empty())
    {
      //write <width>
      ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("description"),
                reinterpret_cast<const xmlChar*>(feed.image().description().c_str()));
      if (ret < 0)
      {
        std::cout << "Error: Could not write <description> element of <image>!" << std::endl;
        xmlFreeTextWriter(writer);
        if (nullptr != document)
          xmlFreeDoc(document);
        return false;
      }
    } //if description
    //close image element
    ret = xmlTextWriterEndElement(writer);
    if (ret < 0)
    {
      std::cout << "Error: Could not end <image> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
  } //if image

  //write <rating>
  if (!feed.rating().empty())
  {
    ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("rating"),
              reinterpret_cast<const xmlChar*>(feed.rating().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write <rating> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
  } //if rating

  //write <textInput>
  if (!feed.textInput().empty())
  {
    //open textInput tag
    ret = xmlTextWriterStartElement(writer, reinterpret_cast<const xmlChar*>("textInput"));
    if (ret < 0)
    {
      std::cout << "Error: Could not start <textInput> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }

    /* All four sub elements are required by the standard, so we can write all
       of them without further checks for emptiness. */
    //write <title>
    ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("title"),
              reinterpret_cast<const xmlChar*>(feed.textInput().title().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write <title> element of <textInput>!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
    //write <description>
    ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("description"),
              reinterpret_cast<const xmlChar*>(feed.textInput().description().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write <description> element of <textInput>!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
    //write <name>
    ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("name"),
              reinterpret_cast<const xmlChar*>(feed.textInput().name().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write <name> element of <textInput>!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
    //write <link>
    ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("link"),
              reinterpret_cast<const xmlChar*>(feed.textInput().link().c_str()));
    if (ret < 0)
    {
      std::cout << "Error: Could not write <link> element of <textInput>!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }

    //close textInput element
    ret = xmlTextWriterEndElement(writer);
    if (ret < 0)
    {
      std::cout << "Error: Could not end <textInput> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
  } //if textInput

  //write <skipHours>
  if (!feed.skipHours().empty())
  {
    //open skipHours tag
    ret = xmlTextWriterStartElement(writer, reinterpret_cast<const xmlChar*>("skipHours"));
    if (ret < 0)
    {
      std::cout << "Error: Could not start <skipHours> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
    //write <hour> tags
    for (const auto hour : feed.skipHours())
    {
      ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("hour"),
                reinterpret_cast<const xmlChar*>(intToString(hour).c_str()));
      if (ret < 0)
      {
        std::cout << "Error: Could not write <hour> element of <skipHours>!" << std::endl;
        xmlFreeTextWriter(writer);
        if (nullptr != document)
          xmlFreeDoc(document);
        return false;
      } //if failure
    } //for
    //close skipHours element
    ret = xmlTextWriterEndElement(writer);
    if (ret < 0)
    {
      std::cout << "Error: Could not end <skipHours> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
  } //if skipHours

  //write <skipDays>
  if (!feed.skipDays().empty())
  {
    //open skipDays tag
    ret = xmlTextWriterStartElement(writer, reinterpret_cast<const xmlChar*>("skipDays"));
    if (ret < 0)
    {
      std::cout << "Error: Could not start <skipDays> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
    //write <days>
    for (const auto day : feed.skipDays())
    {
      ret = xmlTextWriterWriteElement(writer, reinterpret_cast<const xmlChar*>("day"),
                reinterpret_cast<const xmlChar*>(dayToString(day).c_str()));
      if (ret < 0)
      {
        std::cout << "Error: Could not write <day> element of <skipDays>!" << std::endl;
        xmlFreeTextWriter(writer);
        if (nullptr != document)
          xmlFreeDoc(document);
        return false;
      } //if failure
    } //for
    //close skipDays element
    ret = xmlTextWriterEndElement(writer);
    if (ret < 0)
    {
      std::cout << "Error: Could not end <skipDays> element!" << std::endl;
      xmlFreeTextWriter(writer);
      if (nullptr != document)
        xmlFreeDoc(document);
      return false;
    }
  } //if skipDays

  /* xmlTextWriterEndDocument closes all open elements, i.e. <channel> and <rss> in this case. */
  ret = xmlTextWriterEndDocument(writer);
  if (ret < 0)
  {
    std::cout << "Error: Could not end XML document!" << std::endl;
    xmlFreeTextWriter(writer);
    if (nullptr != document)
      xmlFreeDoc(document);
    return false;
  }

  //free writer
  xmlFreeTextWriter(writer);
  writer = nullptr;
  //write file to file given by filename, using UTF-8 encoding and indenting
  ret = xmlSaveFormatFileEnc(fileName.c_str(), document, "UTF-8", 1);
  //free document - it's not used any more
  xmlFreeDoc(document);
  document = nullptr;
  //Did the write fail?
  if (ret < 0)
  {
    std::cout << "Error: Could not write XML document to " << fileName << "!" << std::endl;
    return false;
  }
  return true;
}

} //namespace
