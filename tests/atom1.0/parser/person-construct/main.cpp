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
#include "../../../../src/atom1.0/PersonConstruct.hpp"
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


  const std::unordered_map<std::string, Atom10::PersonConstruct> expectedValues
      = {
          { "person-construct-atom.xml", Atom10::PersonConstruct("Eric Example", "https://eric.example.com/blog/", "eric@example.com") },
          { "person-construct-uri.xml", Atom10::PersonConstruct("Eric Example", "https://eric.example.com/blog/", "") },
          { "person-construct-minimal.xml", Atom10::PersonConstruct("Eric Example", "", "") }
        };

  for (const auto& item : expectedValues)
  {
    //initialize empty person construct
    Atom10::PersonConstruct persConst = Atom10::PersonConstruct();
    const std::string pathToXML = dirForXML + "/" + item.first;
    XMLDocument document = XMLDocument(pathToXML);
    if (!document.isParsed() || document.isEmpty())
    {
      std::cout << "Error: XML document " << pathToXML << " could not be parsed or is empty!" << std::endl;
      return 1;
    }

    if (!Atom10::Parser::personConstructFromNode(document.getRootNode(), persConst, "personConstruct"))
    {
      std::cout << "Error: Could not parse PersonConstruct from " << pathToXML
                << " as Atom 1.0 Person Construct!" << std::endl;
      return 1;
    }

    const Atom10::PersonConstruct& expectedPC = item.second;

    /* Check parsed values against values in XML file. */
    if (!(expectedPC == persConst))
    {
      std::cout << "Error: Parsed Person Construct from " << pathToXML << " does not match the expected Person Construct!" << std::endl;
      //name
      if (persConst.name() != expectedPC.name())
      {
        std::cout << "Error: Unexpected value for person's name: " << persConst.name()
                  << "!" << std::endl;
        return 1;
      }
      //URI
      if (persConst.uri() != expectedPC.uri())
      {
        std::cout << "Error: Unexpected value for person-related URI: " << persConst.uri()
                  << "!" << std::endl;
        return 1;
      }
      //email
      if (persConst.email() != expectedPC.email())
      {
        std::cout << "Error: Unexpected value for email: "
                  << persConst.email() << "!" << std::endl;
        return 1;
      }

      return 1;
    } //if parsed != expected
  } //for

  //All is well, so far.
  return 0;
}
