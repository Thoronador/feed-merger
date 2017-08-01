/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger.
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

#include "Cloud.hpp"

namespace RSS20
{

Cloud::Cloud()
: m_domain(""),
  m_port(-1), //-1 is no valid port, so we know it's "empty"
  m_path(""),
  m_registerProcedure(""),
  m_protocol("")
{
}

Cloud::Cloud(const std::string& domain, const int port,
            const std::string& path, const std::string& registerProcedure,
            const std::string& protocol)
: m_domain(domain),
  m_port(port),
  m_path(path),
  m_registerProcedure(registerProcedure),
  m_protocol(protocol)
{
}

const std::string& Cloud::domain() const
{
  return m_domain;
}

void Cloud::setDomain(const std::string& domain)
{
  m_domain = domain;
}

int Cloud::port() const
{
  return m_port;
}

void Cloud::setPort(const int port)
{
  if (port < 0)
    m_port = -1;
  else
    m_port = port;
}

const std::string& Cloud::path() const
{
  return m_path;
}

void Cloud::setPath(const std::string& path)
{
  m_path = path;
}

const std::string& Cloud::registerProcedure() const
{
  return m_registerProcedure;
}

void Cloud::setRegisterProcedure(const std::string& registerProcedure)
{
  m_registerProcedure = registerProcedure;
}

const std::string& Cloud::protocol() const
{
  return m_protocol;
}

void Cloud::setProtocol(const std::string& protocol)
{
  m_protocol = protocol;
}

const bool Cloud::empty() const
{
  return (m_domain.empty() and (m_port < 0) and m_path.empty()
          and m_registerProcedure.empty() and m_protocol.empty());
}

bool Cloud::operator==(const Cloud& other) const
{
  return ((m_domain == other.m_domain) && (m_port == other.m_port)
       && (m_path == other.m_path) && (m_registerProcedure == other.m_registerProcedure)
       && (m_protocol == other.m_protocol));
}

} //namespace
