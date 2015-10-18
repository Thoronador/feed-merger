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

#ifndef XMLNODE_HPP
#define XMLNODE_HPP

#include <string>
#include <libxml/tree.h>

/** \brief This is a C++-style wrapper class for libxml(2)'s xmlNodePtr type.
*/
class XMLNode
{
  public:
    /** \brief constructor
     *
     * \param node - the libxml node pointer we are wrapping in this class
     */
    XMLNode(const xmlNodePtr node);


    /** returns the node's name as pointer to a C-style string */
    inline const xmlChar* getName() const
    {
      return m_Node->name;
    }


    /** returns the node's name as an STL string */
    inline std::string getNameAsString() const
    {
      return reinterpret_cast<const char*>(m_Node->name);
    }


    /** returns true, if the node has at least one child node */
    inline bool hasChild() const
    {
      return (m_Node->children!=NULL);
    }


    /** returns true, if the node has at least one more sibling */
    inline bool hasNextSibling() const
    {
      return (m_Node->next!=NULL);
    }


    /** returns true, if the node has at least one previous sibling */
    inline bool hasPrevSibling() const
    {
      return (m_Node->prev!=NULL);
    }


    /** returns true, if the node has a parent node */
    inline bool hasParent() const
    {
      return (m_Node->parent!=NULL);
    }


    /** returns true, if the node has a parent node */
    inline bool hasAttribute() const
    {
      return (m_Node->properties!=NULL);
    }


    /** returns the first child of the node. Throws an exception, if there is no
        child node.
    */
    inline XMLNode getChild() const
    {
      return m_Node->children;
    }

    /** returns the next sibling of the node. Throws an exception, if there is no
        next sibling.
    */
    inline XMLNode getNextSibling() const
    {
      return m_Node->next;
    }


    /** returns the previous sibling of the node. Throws an exception, if there
        is no previous sibling.
    */
    inline XMLNode getPrevSibling() const
    {
      return m_Node->prev;
    }


    /** returns the name of the node's first attribute. Returns an empty string,
       if there is no attribute for that node.
    */
    std::string getFirstAttributeName() const;


    /** returns the value of the node's first attribute. Returns an empty string,
       if there is no attribute for that node or the attribute has no value.
    */
    std::string getFirstAttributeValue() const;

    /** returns the parent of the node. Throws an exception, if there is no
       parent node.
    */
    inline XMLNode getParent() const
    {
      return m_Node->parent;
    }


    /** returns true, if the node is an element node */
    inline bool isElementNode() const
    {
      return (m_Node->type==XML_ELEMENT_NODE);
    }


    /** returns true, if the node is an attribute node */
    inline bool isAttributeNode() const
    {
      return (m_Node->type==XML_ATTRIBUTE_NODE);
    }

    /** returns true, if the node is a text node */
    bool isTextNode() const
    {
      return (m_Node->type==XML_TEXT_NODE);
    }


    /** returns the text contained in the node, if it's a text node.  If there is no
        text node (or any child node), the function will return an empty string.
    */
    std::string getPlainTextContent() const;


    /** returns the text contained in the node's CDATA section. If there is no
       CDATA section (or any child node), the function will return an empty
       string.
    */
    std::string getCDATAText() const;


    /** get content for both - either CDATA or text node. If there is no child
       node, or the child node is neither e CDATA nor a text node, the function
       will return an empty string.
    */
    std::string getContentBoth() const;
  private:
    xmlNodePtr m_Node;
};//class

#endif // XMLNODE_HPP
