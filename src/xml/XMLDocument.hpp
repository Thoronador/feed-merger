/*
 -------------------------------------------------------------------------------
    This file is part of the Private Message Database.
    Copyright (C) 2012, 2014  Thoronador

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

#ifndef XMLDOCUMENT_HPP
#define XMLDOCUMENT_HPP

#include <string>
#include <libxml/tree.h>
#include "XMLNode.hpp"

/** \brief This is a C++-style wrapper class for libxml(2)'s xmlDoc type.
*/
class XMLDocument
{
  public:
    /** \brief constructor
     *
     * \param fileName   path to the XML document that shall be wrapped inside this class
     */
    XMLDocument(const std::string& fileName);


    /** copy constructor */
    XMLDocument(const XMLDocument& op);


    /** assignment operator */
    XMLDocument& operator=(const XMLDocument& op);


    /** destructor */
    virtual ~XMLDocument();


    /** returns true, if the document is parsed (i.e. a valid document) */
    bool isParsed() const;

    /** returns true, if the document is empty */
    bool isEmpty() const;

    /** returns true, if the document is well formed */
    bool wellFormed() const;

    /** returns the document's root node, or throws an exception if the document
       is either not parsed or empty
    */
    XMLNode getRootNode() const;
  private:
    xmlDocPtr m_Doc;
};//class

#endif // XMLDOCUMENT_HPP
