/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger.
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

#ifndef RSS20_CLOUD_HPP
#define RSS20_CLOUD_HPP

#include <string>

namespace RSS20
{
  /** \brief class that represents the <cloud> element in a RSS 2.0 channel
   *
   * The <cloud> elements holds cloud information for lightweight
   * publish-subscribe protocol in RSS 2.0.
   */
  class Cloud
  {
    public:
      /** \brief default constructor - sets all members to empty state
       */
      Cloud();


      /** \brief constructor with initial values
       *
       * \param domain  server domain
       * \param port    port for connection
       * \param path    path on the server
       * \param registerProcedure   procedure that shall be called
       * \param protocol   protocol that shall be used for the connection
       */

      Cloud(const std::string& domain, const int port,
            const std::string& path, const std::string& registerProcedure,
            const std::string& protocol);


      /** \brief returns the server's domain
       *
       * \return Returns the domain of the server.
       */
      const std::string& domain() const;


      /** \brief sets a new domain
       *
       * \param domain  the new domain name
       */
      void setDomain(const std::string& domain);


      /** \brief returns the server's port for the connection
       *
       * \return Returns the server's port for the connection.
       *         Values less or equal to zero indicate that no port
       *         has been set yet.
       */
      int port() const;


      /** \brief sets a new port
       *
       * \param port  the new domain name
       */
      void setPort(const int port);


      /** \brief returns the path on the server
       *
       * \return Returns the path on the server
       */
      const std::string& path() const;


      /** \brief sets a new path
       *
       * \param path  the new path on the server
       */
      void setPath(const std::string& path);


      /** \brief gets the procedure call
       *
       * \return Returns the procedure call.
       */
      const std::string& registerProcedure() const;


      /** \brief sets a new procedure call
       *
       * \param registerProcedure  the new procedure call to be registered
       */
      void setRegisterProcedure(const std::string& registerProcedure);


      /** \brief returns the connection protocol
       *
       * \return Returns the connection protocol.
       */
      const std::string& protocol() const;


      /** \brief sets a new connection protocol
       *
       * \param protocol  the new connection protocol
       * \remarks Possible protocols include "soap" for SOAP 1.1,
       *          "xml-rpc" for XML-RPC and "http-post"(That's a guess. The
       *          corresponding value is not clearly stated in the RSS 2.0
       *          specification.) for HTTP-POST.
       */
      void setProtocol(const std::string& protocol);


      /** \brief checks whether this element is empty
       *
       * \return Returns true, if this element is empty.
       * Returns false, if it contains some data.
       */
      const bool empty() const;


      /** \brief equality operator for Enclosure
       *
       * \param other  the other instance
       * \return Returns true, if both instances are equal.
       */
      bool operator==(const Cloud& other) const;
    private:
      std::string m_domain; /**< the domain of the server */
      int m_port; /**< port that is used for the connection */
      std::string m_path; /**< path on server, e.g. "/dir2" */
      std::string m_registerProcedure; /**< procedure call */
      std::string m_protocol; /**< protocol for the procedure */
  }; //class
} //namespace

#endif // RSS20_CLOUD_HPP
