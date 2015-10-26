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

#ifndef RSS20_IMAGE_HPP
#define RSS20_IMAGE_HPP

#include <string>

namespace RSS20
{

  class Image
  {
    public:
      /** \brief default constructor - initializes all members with empty values
       */
      Image();


      #warning Add code documentation for RSS20::Image!
      Image(const std::string& url, const std::string& title,
            const std::string& link, const int width, const int height,
            const std::string& description);

      const std::string& url() const;

      void setUrl(const std::string& url);

      const std::string& title() const;

      void setTitle(const std::string& title);

      const std::string& link() const;

      void setLink(const std::string& link);

      int width() const;

      void setWidth(const int width);

      int height() const;

      void setHeight(const int height);

      const std::string& description() const;

      void setDescription(const std::string& description);

      bool empty() const;

      bool operator==(const Image& other) const;
    private:
      //required elements: url, title, link
      std::string m_url; /**< URL of a GIF, JPEG or PNG that represents the channel */
      std::string m_title; /**< describes the image */
      std::string m_link; /**< link to the site */
      //optional elements: width, height, description
      int m_width; /**< width of image */
      int m_height; /**< height of image */
      std::string m_description; /**< text that is included in the title attribute
                                      of the link formed around the image in
                                      the HTML rendering */
  }; //class
} //namespace

#endif // RSS20_IMAGE_HPP
