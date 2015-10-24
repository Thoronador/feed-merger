/*
 -------------------------------------------------------------------------------
    This file is part of the Private Message Database.
    Copyright (C) 2012, 2014, 2015  Thoronador

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

#include "XMLDocument.hpp"
#include <stdexcept>

XMLDocument::XMLDocument(const std::string& fileName)
: //parse the XML file
  m_Doc(xmlParseFile(fileName.c_str()))
{}

XMLDocument::XMLDocument(xmlDocPtr doc)
: //use existing pointer
  m_Doc(doc)
{}

XMLDocument::XMLDocument(const XMLDocument& op)
: m_Doc(op.m_Doc==NULL ? NULL : xmlCopyDoc(op.m_Doc, 1))
{
}

XMLDocument& XMLDocument::operator=(const XMLDocument& op)
{
  if (this==&op) return *this;
  xmlFreeDoc(m_Doc);
  m_Doc = NULL;
  if (op.m_Doc!=NULL)
  {
    m_Doc = xmlCopyDoc(op.m_Doc, 1);
  }
  return *this;
}

XMLDocument::~XMLDocument()
{
  xmlFreeDoc(m_Doc);
}

bool XMLDocument::isParsed() const
{
  return (m_Doc!=NULL);
}

bool XMLDocument::isEmpty() const
{
  return (xmlDocGetRootElement(m_Doc)==NULL);
}

bool XMLDocument::wellFormed() const
{
  if (NULL!=m_Doc)
    return ((m_Doc->properties & XML_DOC_WELLFORMED) != 0);
  return false;
}

XMLNode XMLDocument::getRootNode() const
{
  if (!isParsed() or isEmpty())
    throw std::invalid_argument("XMLDocument::getRootNode(): XML document must be parsed and not empty, if you want to get the root node!");
  return XMLNode(xmlDocGetRootElement(m_Doc));
}
