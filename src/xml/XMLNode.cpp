/*
 -------------------------------------------------------------------------------
    This file is part of the Private Message Database.
    Copyright (C) 2012, 2013, 2014  Thoronador

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

#include "XMLNode.hpp"
#include <stdexcept>

XMLNode::XMLNode(const xmlNodePtr node)
: m_Node(node)
{
  if (NULL==node)
    throw std::invalid_argument("NULL is not allowed as argument in XMLNode::XMLNode()!"); //NULL not allowed
}

std::string XMLNode::getPlainTextContent() const
{
  //text is a child node of current node, so it has to have a child
  if (NULL==m_Node->children) return "";
  //type should be text node, of course
  if (m_Node->children->type!=XML_TEXT_NODE) return "";
  xmlChar* key = xmlNodeListGetString(m_Node->doc, m_Node->children, 1);
  std::string result = reinterpret_cast<const char*>(key);
  xmlFree(key);//free it, because xmlNodeListGetString() allocated memory
  return result;
}

std::string XMLNode::getCDATAText() const
{
  //text is a child node of current node, so it has to have a child
  if (NULL==m_Node->children) return "";
  //type should be CTDA node, of course
  if (m_Node->children->type!=XML_CDATA_SECTION_NODE) return "";
  xmlChar* key = xmlNodeListGetString(m_Node->doc, m_Node->children, 1);
  std::string result = reinterpret_cast<const char*>(key);
  xmlFree(key);//free it, because xmlNodeListGetString() allocated memory
  return result;
}

std::string XMLNode::getContentBoth() const
{
  //text is a child node of current node, so it has to have a child
  if (NULL==m_Node->children) return "";
  //type should be text or CDATA node
  if ((m_Node->children->type!=XML_TEXT_NODE) and (m_Node->children->type!=XML_CDATA_SECTION_NODE)) return "";
  xmlChar* key = xmlNodeListGetString(m_Node->doc, m_Node->children, 1);
  std::string result = reinterpret_cast<const char*>(key);
  xmlFree(key);//free it, because xmlNodeListGetString() allocated memory
  return result;
}

std::string XMLNode::getFirstAttributeName() const
{
  //if there are no attribute nodes, return empty string
  if (NULL==m_Node->properties) return "";
  return reinterpret_cast<const char*>(m_Node->properties->name);
}

std::string XMLNode::getFirstAttributeValue() const
{
  //if there are no attribute nodes, return empty string
  if (NULL==m_Node->properties) return "";
  //if there is no content, return empty string
  if (NULL==m_Node->properties->children) return "";
  //return content of first attr node
  return reinterpret_cast<const char*>(m_Node->properties->children->content);
}
