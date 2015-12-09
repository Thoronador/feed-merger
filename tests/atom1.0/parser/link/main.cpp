/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger test suite.
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

#include <iostream>
#include <unordered_map>
#include "../../../../src/atom1.0/Parser.hpp"
#include "../../../../src/atom1.0/Link.hpp"
#include "../../../../src/xml/XMLDocument.hpp"

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cout << "Error: Expecting exactly one argument (file name)."
              << std::endl;
    return 1;
  }

  if ((argv == nullptr) || (argv[1] == nullptr))
  {
    std::cout << "Error: Argument is null!" << std::endl;
    return 1;
  }

  const std::string dirForXML = std::string(argv[1]);


  const std::unordered_map<std::string, Atom10::Link> expectedValues
      = {
          { "link-atom.xml", Atom10::Link("https://link.example.com/directory/a.ps", "alternate", "application/postscript", "en-GB", "I am a title!", 1234567890) },
          { "link-minimal.xml", Atom10::Link("https://link.example.com/directory/a.ps", "", "", "", "", 0) },
          { "link-related.xml", Atom10::Link("https://link.example.com/directory/a.ps", "related", "", "", "", 0) },
          { "link-type.xml", Atom10::Link("https://link.example.com/directory/a.ps", "", "application/postscript", "", "", 0) }
        };

  for (const auto& item : expectedValues)
  {
    //initialize empty link
    Atom10::Link link = Atom10::Link();
    const std::string pathToXML = dirForXML + "/" + item.first;
    XMLDocument document = XMLDocument(pathToXML);
    if (!document.isParsed() || document.isEmpty())
    {
      std::cout << "Error: XML document " << pathToXML << " could not be parsed or is empty!" << std::endl;
      return 1;
    }

    if (!Atom10::Parser::linkFromNode(document.getRootNode(), link))
    {
      std::cout << "Error: Could not parse Link from " << pathToXML
                << " as Atom 1.0 link!" << std::endl;
      return 1;
    }

    const Atom10::Link& expectedLink = item.second;

    /* Check parsed values against values in XML file. */
    if (!(expectedLink == link))
    {
      std::cout << "Error: Parsed link from " << pathToXML << " does not match the expected link!" << std::endl;
      //href
      if (link.href() != expectedLink.href())
      {
        std::cout << "Error: Unexpected value for link's href: " << link.href()
                  << "!" << std::endl;
        return 1;
      }
      //rel
      if (link.rel() != expectedLink.rel())
      {
        std::cout << "Error: Unexpected value for rel: " << link.rel()
                  << "!" << std::endl;
        return 1;
      }
      //type
      if (link.type() != expectedLink.type())
      {
        std::cout << "Error: Unexpected value for type: "
                  << link.type() << "!" << std::endl;
        return 1;
      }
      //hreflang
      if (link.hreflang() != expectedLink.hreflang())
      {
        std::cout << "Error: Unexpected value for hreflang: "
                  << link.hreflang() << "!" << std::endl;
        return 1;
      }
      //title
      if (link.title() != expectedLink.title())
      {
        std::cout << "Error: Unexpected value for title: "
                  << link.title() << "!" << std::endl;
        return 1;
      }
      //length
      if (link.length() != expectedLink.length())
      {
        std::cout << "Error: Unexpected value for length: "
                  << link.length() << "! Expected value is "
                  << expectedLink.length() << std::endl;
        return 1;
      }
      return 1;
    } //if parsed != expected
  } //for

  //All is well, so far.
  std::cout << "Passed parser tests for Atom 1.0 <link> element." << std::endl;
  return 0;
}
