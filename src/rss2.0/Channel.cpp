/*
 -------------------------------------------------------------------------------
    This file is part of the feed merger.
    Copyright (C) 2015, 2017  Dirk Stolle

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

#include "Channel.hpp"

namespace RSS20
{

Channel::Channel()
: BasicRSS::Channel(),
  m_items(std::vector<Item>()),
  m_category(std::set<Category>()),
  m_generator(""),
  m_cloud(Cloud()),
  m_ttl(-1)
{
}

Channel::Channel(const std::string& title, const std::string& link,
              const std::string& description, const std::vector<Item>& items,
              const std::string& language, const std::string& copyright,
              const std::string& managingEditor, const std::string& webMaster,
              const std::time_t pubDate, const std::time_t lastBuildDate,
              const std::set<Category>& category, const std::string& generator,
              const std::string& docs, const Cloud& cloud,
              const int ttl, const Image& image,
              const std::string& rating, const TextInput& textInput,
              const std::set<unsigned int>& skipHours,
              const std::set<BasicRSS::Days>& skipDays)
: BasicRSS::Channel(title, link, description, language, copyright,
                    managingEditor, webMaster, pubDate, lastBuildDate, docs,
                    image, rating, textInput, skipHours, skipDays),
  m_items(items),
  m_category(category),
  m_generator(generator),
  m_cloud(cloud),
  m_ttl(ttl)
{
}

const std::vector<Item>& Channel::items() const
{
  return m_items;
}

void Channel::addItem(const Item& item)
{
  if (!item.empty())
    m_items.push_back(item);
}

void Channel::setItems(const std::vector<Item>& all)
{
  m_items = all;
  //remove empty items
  for (auto i = m_items.begin(); i != m_items.end(); /*no-op*/)
  {
    if (i->empty())
      i = m_items.erase(i);
    else
      ++i;
  } //for
}

const std::set<Category>& Channel::category() const
{
  return m_category;
}

void Channel::setCategory(const std::set<Category>& category)
{
  m_category = category;
}

void Channel::addCategory(const Category& category)
{
  m_category.insert(category);
}

const std::string& Channel::generator() const
{
  return m_generator;
}

void Channel::setGenerator(const std::string& generator)
{
  m_generator = generator;
}

const Cloud& Channel::cloud() const
{
  return m_cloud;
}

void Channel::setCloud(const Cloud& cloud)
{
  m_cloud = cloud;
}

int Channel::ttl() const
{
  return m_ttl;
}

void Channel::setTtl(const int ttl)
{
  m_ttl = ttl;
}

bool Channel::operator==(const Channel& other) const
{
  return (BasicRSS::Channel::operator==(other)
      && (m_items == other.m_items) && (m_category == other.m_category)
      && (m_generator == other.m_generator) && (m_cloud == other.m_cloud)
      && (m_ttl == other.m_ttl)
    );
}

bool Channel::operator!=(const Channel& other) const
{
  /* Inequality operator is the negation of the equality operator. */
  return (!(*this == other));
}

} //namespace
