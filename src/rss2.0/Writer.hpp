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

#ifndef RSS20_WRITER_HPP
#define RSS20_WRITER_HPP

#include <libxml/xmlwriter.h>
#include "Channel.hpp"

namespace RSS20
{

  class Writer
  {
    public:
      /** \brief tries to write a given feed to a file
       *
       * \param feed  the RSS 2.0 feed
       * \param fileName  name of the output file
       * \return Returns true, if file was written successfully.
       * Returns false, if an error occurred.
       */
      static bool toFile(const Channel& feed, const std::string& fileName);
    private:
      /** \brief tries to write a category element with the help of an XML text writer (libxml2)
       *
       * \param cat   the category that shall be written
       * \param writer xmlTextWriterPtr for the writer
       * \return Returns true, if the operation was successful.
       * Returns false, if the operation failed.
       */
      static bool writeCategory(const Category& cat, xmlTextWriterPtr writer);


      /** \brief tries to write a given feed item with the help of an XML text writer (libxml2)
       *
       * \param item   the item that shall be written
       * \param writer xmlTextWriterPtr for the writer
       * \return Returns true, if the operation was successful.
       * Returns false, if the operation failed.
       */
      static bool writeItem(const Item& item, xmlTextWriterPtr writer);
  }; //class
} //namespace

#endif // RSS20_WRITER_HPP
