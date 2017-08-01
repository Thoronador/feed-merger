/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger test suite.
    Copyright (C) 2015  Dirk Stolle

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
#include "../../../../src/atom1.0/Category.hpp"
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


  const std::unordered_map<std::string, Atom10::Category> expectedValues
      = {
          { "category-atom.xml", Atom10::Category("example", "https://cat.example.com/scheme/", "Example") },
          { "category-label.xml", Atom10::Category("example", "", "Example") },
          { "category-minimal.xml", Atom10::Category("example", "", "") },
          { "category-scheme.xml", Atom10::Category("example", "https://cat.example.com/scheme/", "") }
        };

  for (const auto& item : expectedValues)
  {
    //initialize empty person construct
    Atom10::Category categ = Atom10::Category();
    const std::string pathToXML = dirForXML + "/" + item.first;
    XMLDocument document = XMLDocument(pathToXML);
    if (!document.isParsed() || document.isEmpty())
    {
      std::cout << "Error: XML document " << pathToXML << " could not be parsed or is empty!" << std::endl;
      return 1;
    }

    if (!Atom10::Parser::categoryFromNode(document.getRootNode(), categ))
    {
      std::cout << "Error: Could not parse Category from " << pathToXML
                << " as Atom 1.0 category!" << std::endl;
      return 1;
    }

    const Atom10::Category& expectedCat = item.second;

    /* Check parsed values against values in XML file. */
    if (!(expectedCat == categ))
    {
      std::cout << "Error: Parsed category from " << pathToXML << " does not match the expected category!" << std::endl;
      //term
      if (categ.term() != expectedCat.term())
      {
        std::cout << "Error: Unexpected value for category's term: " << categ.term()
                  << "!" << std::endl;
        return 1;
      }
      //scheme
      if (categ.scheme() != expectedCat.scheme())
      {
        std::cout << "Error: Unexpected value for scheme IRI: " << categ.scheme()
                  << "!" << std::endl;
        return 1;
      }
      //label
      if (categ.label() != expectedCat.label())
      {
        std::cout << "Error: Unexpected value for label: "
                  << categ.label() << "!" << std::endl;
        return 1;
      }

      return 1;
    } //if parsed != expected
  } //for

  //All is well, so far.
  return 0;
}
