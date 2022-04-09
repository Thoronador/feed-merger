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

#ifndef RSS20_PROTOCOL_HPP
#define RSS20_PROTOCOL_HPP

#include <string>

namespace RSS20
{
  /** \brief Represents the protocol of a <cloud> element in an RSS 2.0 channel.
   */
  enum class Protocol
  {
      /// no protocol set
      none,

      /// XML-RPC
      XmlRpc,

      /// SOAP 1.1
      Soap,

      /// REST via HTTP
      HttpPost
  };

  /** \brief Gets the string representation of a protocol value.
   *
   * \param p  the protocol
   * \return Returns the string representation of a protocol value as seen in
   *         the RSS 2.0 cloud element.
   */
  std::string to_string(const Protocol p);

  /** \brief Transforms the string representation of a protocol into the
   *         corresponding enumeration value.
   *
   * \param s   the string value
   * \return Returns the corresponding enumeration value.
   *         Returns Protocol::none, if the string is not a valid representation.
   */
  Protocol from_string(std::string s);
} // namespace

#endif // RSS20_PROTOCOL_HPP
