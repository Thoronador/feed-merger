/*
 -------------------------------------------------------------------------------
    This file is part of the Private Message Database.
    Copyright (C) 2012, 2013, 2014, 2015  Thoronador

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
    const xmlChar* getName() const;


    /** returns the node's name as an STL string */
    std::string getNameAsString() const;


    /** returns true, if the node has at least one child node */
    bool hasChild() const;


    /** returns true, if the node has at least one more sibling */
    bool hasNextSibling() const;


    /** returns true, if the node has at least one previous sibling */
    bool hasPrevSibling() const;


    /** returns true, if the node has a parent node */
    bool hasParent() const;


    /** returns true, if the node has a parent node */
    bool hasAttribute() const;


    /** returns the first child of the node. Throws an exception, if there is no
        child node.
    */
    XMLNode getChild() const;

    /** returns the next sibling of the node. Throws an exception, if there is no
        next sibling.
    */
    XMLNode getNextSibling() const;


    /** returns the previous sibling of the node. Throws an exception, if there
        is no previous sibling.
    */
    XMLNode getPrevSibling() const;


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
    XMLNode getParent() const;


    /** returns true, if the node is an element node */
    bool isElementNode() const;


    /** returns true, if the node is an attribute node */
    bool isAttributeNode() const;

    /** returns true, if the node is a text node */
    bool isTextNode() const;


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
