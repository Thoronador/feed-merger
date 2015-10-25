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

#include "Channel.hpp"

namespace RSS20
{

Channel::Channel()
: m_title(""),
  m_link(""),
  m_description(""),
  m_items(std::vector<Item>()),
  m_language(""),
  m_copyright(""),
  m_managingEditor(""),
  m_webMaster(""),
  m_pubDate(static_cast<std::time_t>(0)),
  m_lastBuildDate(static_cast<std::time_t>(0)),
  m_category(Category()),
  m_generator(""),
  m_docs(""),
  m_ttl(-1)
{
}

Channel::Channel(const std::string& title, const std::string& link,
              const std::string& description, const std::vector<Item>& items,
              const std::string& language, const std::string& copyright,
              const std::string& managingEditor, const std::string& webMaster,
              const std::time_t pubDate, const std::time_t lastBuildDate,
              const Category& category, const std::string& generator,
              const std::string& docs, const int ttl)
: m_title(title),
  m_link(link),
  m_description(description),
  m_items(items),
  m_language(language),
  m_copyright(copyright),
  m_managingEditor(managingEditor),
  m_webMaster(webMaster),
  m_pubDate(pubDate),
  m_lastBuildDate(lastBuildDate),
  m_category(category),
  m_generator(generator),
  m_docs(docs),
  m_ttl(ttl)
{
}

const std::string& Channel::title() const
{
  return m_title;
}

void Channel::setTitle(const std::string& title)
{
  m_title = title;
}

const std::string& Channel::link() const
{
  return m_link;
}

void Channel::setLink(const std::string& link)
{
  m_link = link;
}

const std::string& Channel::description() const
{
  return m_description;
}

void Channel::setDescription(const std::string& description)
{
  m_description = description;
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

const std::string& Channel::language() const
{
  return m_language;
}

void Channel::setLanguage(const std::string& language)
{
  m_language = language;
}

const std::string& Channel::copyright() const
{
  return m_copyright;
}

void Channel::setCopyright(const std::string& copyright)
{
  m_copyright = copyright;
}

const std::string& Channel::managingEditor() const
{
  return m_managingEditor;
}

void Channel::setManagingEditor(const std::string& managingEditor)
{
  m_managingEditor = managingEditor;
}

const std::string& Channel::webMaster() const
{
  return m_webMaster;
}

void Channel::setWebMaster(const std::string& webMaster)
{
  m_webMaster = webMaster;
}

std::time_t Channel::pubDate() const
{
  return m_pubDate;
}

void Channel::setPubDate(const std::time_t pubDate)
{
  m_pubDate = pubDate;
}

std::time_t Channel::lastBuildDate() const
{
  return m_lastBuildDate;
}

void Channel::setLastBuildDate(const std::time_t lastBuildDate)
{
  m_lastBuildDate = lastBuildDate;
}

const Category& Channel::category() const
{
  return m_category;
}

void Channel::setCategory(const Category& category)
{
  m_category = category;
}

const std::string& Channel::generator() const
{
  return m_generator;
}

void Channel::setGenerator(const std::string& generator)
{
  m_generator = generator;
}

const std::string& Channel::docs() const
{
  return m_docs;
}

void Channel::setDocs(const std::string& docs)
{
  m_docs = docs;
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
  return ((m_title == other.m_title) && (m_link == other.m_link)
      && (m_description == other.m_description) && (m_items == other.m_items)
      && (m_language == other.m_language) && (m_copyright == other.m_copyright)
      && (m_managingEditor == other.m_managingEditor) && (m_webMaster == other.m_webMaster)
      && (m_pubDate == other.m_pubDate) && (m_lastBuildDate == other.m_lastBuildDate)
      && (m_category == other.m_category) && (m_generator == other.m_generator)
      && (m_docs == other.m_docs) && (m_ttl == other.m_ttl)
    );
}

} //namespace
