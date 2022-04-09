/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger.
    Copyright (C) 2022  Dirk Stolle

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

#include "Protocol.hpp"
#include <algorithm>
#include <cctype>

namespace RSS20
{

std::string to_string(const Protocol p)
{
  switch (p)
  {
    case Protocol::XmlRpc:
         return "xml-rpc";
    case Protocol::Soap:
         return "soap";
    case Protocol::HttpPost:
         return "http-post";
    default:
         return "";
  }
}

Protocol from_string(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c){ return std::tolower(c); }
                );

  if (s == "xml-rpc")
    return Protocol::XmlRpc;
  if (s == "soap")
    return Protocol::Soap;
  if (s == "http-post")
    return Protocol::HttpPost;
  // Everything else is a value that is not part of the specification, so just
  // return none here.
  return Protocol::none;
}

} // namespace
