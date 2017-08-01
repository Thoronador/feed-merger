/*
 -------------------------------------------------------------------------------
    This file is part of the Private Message Database.
    Copyright (C) 2012, 2013, 2014, 2015  Dirk Stolle

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
#include "../StringFunctions.hpp"

XMLNode::XMLNode(const xmlNodePtr node)
: m_Node(node)
{
  if (NULL==node)
    throw std::invalid_argument("NULL is not allowed as argument in XMLNode::XMLNode()!"); //NULL not allowed
}

const xmlChar* XMLNode::getName() const
{
  return m_Node->name;
}

std::string XMLNode::getNameAsString() const
{
  return reinterpret_cast<const char*>(m_Node->name);
}

bool XMLNode::hasChild() const
{
  return (m_Node->children!=NULL);
}

bool XMLNode::hasNextSibling() const
{
  return (m_Node->next!=NULL);
}

bool XMLNode::hasPrevSibling() const
{
  return (m_Node->prev!=NULL);
}

bool XMLNode::hasParent() const
{
  return (m_Node->parent!=NULL);
}

bool XMLNode::hasAttribute() const
{
  return (m_Node->properties!=NULL);
}

XMLNode XMLNode::getChild() const
{
  return m_Node->children;
}

XMLNode XMLNode::getNextSibling() const
{
  return m_Node->next;
}

XMLNode XMLNode::getPrevSibling() const
{
  return m_Node->prev;
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

std::vector<std::pair<std::string, std::string> > XMLNode::getAttributes() const
{
  //if there are no attribute nodes, return empty vector
  if (NULL==m_Node->properties)
    return std::vector<std::pair<std::string, std::string> >();

  std::vector<std::pair<std::string, std::string> > attributeList;
  xmlAttrPtr currentAttribute = m_Node->properties;
  while (currentAttribute != NULL)
  {
    std::string value = "";
    if (currentAttribute->children != NULL)
      value = reinterpret_cast<const char*>(currentAttribute->children->content);
    //push name and value to list
    attributeList.push_back(std::pair<std::string, std::string>(
        reinterpret_cast<const char*>(currentAttribute->name), value));
    //move to next attribute
    currentAttribute = currentAttribute->next;
  } //while
  return attributeList;
}

XMLNode XMLNode::getParent() const
{
  return m_Node->parent;
}

bool XMLNode::isElementNode() const
{
  return (m_Node->type==XML_ELEMENT_NODE);
}

bool XMLNode::isAttributeNode() const
{
  return (m_Node->type==XML_ATTRIBUTE_NODE);
}

bool XMLNode::isTextNode() const
{
  return (m_Node->type==XML_TEXT_NODE);
}

bool XMLNode::isCommentNode() const
{
  return (m_Node->type==XML_COMMENT_NODE);
}

void XMLNode::skipEmptyCommentAndTextSiblings()
{
  while ((isCommentNode() or (isTextNode() and isEmptyOrWhitespace(getContentBoth())))
          and hasNextSibling())
  {
    m_Node = m_Node->next;
  } //while)
}
