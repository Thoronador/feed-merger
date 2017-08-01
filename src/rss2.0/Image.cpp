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

#include "Image.hpp"

namespace RSS20
{

Image::Image()
: m_url(""),
  m_title(""),
  m_link(""),
  m_width(-1),
  m_height(-1),
  m_description("")
{
}


Image::Image(const std::string& url, const std::string& title,
            const std::string& link, const int width, const int height,
            const std::string& description)
: m_url(url),
  m_title(title),
  m_link(link),
  m_width(width),
  m_height(height),
  m_description(description)
{
}

const std::string& Image::url() const
{
  return m_url;
}

void Image::setUrl(const std::string& url)
{
  m_url = url;
}

const std::string& Image::title() const
{
  return m_title;
}

void Image::setTitle(const std::string& title)
{
  m_title = title;
}

const std::string& Image::link() const
{
  return m_link;
}

void Image::setLink(const std::string& link)
{
  m_link = link;
}

int Image::width() const
{
  return m_width;
}

void Image::setWidth(const int width)
{
  m_width = width;
}

int Image::height() const
{
  return m_height;
}

void Image::setHeight(const int height)
{
  m_height = height;
}

const std::string& Image::description() const
{
  return m_description;
}

void Image::setDescription(const std::string& description)
{
  m_description = description;
}

bool Image::empty() const
{
  return (m_url.empty() and m_title.empty() and m_link.empty()
      && (m_width <= 0) and (m_height <= 0) and m_description.empty());
}

bool Image::operator==(const Image& other) const
{
  return ((m_url == other.m_url) and (m_title == other.m_title)
      and (m_link == other.m_link) and (m_width == other.m_width)
      and (m_height == other.m_height) and (m_description == other.m_description)
    );
}

} //namespace
