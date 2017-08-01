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


      /** \brief constructor with initial values
       *
       * \param url      URL of a GIF, JPEG or PNG that represents the channel
       * \param title    title to describe the image
       * \param link     URL of the site
       * \param width    width of the image
       * \param height   height if the image
       * \param description   text that is included in the title attribute of
       *                      the link formed around the image in the HTML rendering
       */
      Image(const std::string& url, const std::string& title,
            const std::string& link, const int width, const int height,
            const std::string& description);


      /** \brief returns the URL of the image
       *
       * \return Returns URL of the image.
       */
      const std::string& url() const;


      /** \brief sets the URL of the image
       *
       * \param url the new URL of the image
       */
      void setUrl(const std::string& url);


      /** \brief returns the title of the image
       *
       * \return Returns title of the image.
       */
      const std::string& title() const;


      /** \brief sets the title
       *
       * \param title  the new title of the image
       */
      void setTitle(const std::string& title);


      /** \brief returns link to the site
       *
       * \return Returns the link to the site.
       */
      const std::string& link() const;


      /** \brief sets the link to the site
       *
       * \param link  the new link URL
       */
      void setLink(const std::string& link);


      /** \brief returns given image width in pixels
       *
       * \return Returns the image width specified with "width".
       */
      int width() const;


      /** \brief sets the new image width
       *
       * \param width  the new image width
       */
      void setWidth(const int width);


      /** \brief returns given image height in pixels
       *
       * \return Returns the image height specified with "height".
       */
      int height() const;


      /** \brief sets the new image height
       *
       * \param height  the new image height
       */
      void setHeight(const int height);


      /** \brief gets the description
       *
       * \return Returns the text that is included in the title attribute of
       *         the link formed around the image in the HTML rendering.
       */
      const std::string& description() const;


      /** \brief sets a new description
       *
       * \param description the new description
       */
      void setDescription(const std::string& description);


      /** \brief checks whether this element is empty
       *
       * \return Returns true, if this element is empty.
       * Returns false, if it contains some data.
       */
      bool empty() const;


      /** \brief equality operator for Image
       *
       * \param other  the other instance
       * \return Returns true, if both instances are equal.
       */
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
