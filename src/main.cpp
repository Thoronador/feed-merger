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

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include "Curly.hpp"
#include "rss2.0/Channel.hpp"
#include "rss2.0/Parser.hpp"
#include "rss2.0/Writer.hpp"
#include "StringFunctions.hpp"

//Return code that indicates invalid command line arguments.
const int rcInvalidParameter = 1;
//Return code that indicates some network-related problem.
const int rcNetworkError = 2;
//Return code that indicates that some data could not be parsed as feed.
const int rcParserError = 3;
//Return code that indicates some I/O-related error with the file system.
const int rcFileError = 4;

//The default output file name that is used if no file name is given.
const std::string cDefaultOutputFileName = "merged-feeds.xml";

//strings that indicate the program's version
const std::string cVersionString( "feed-merger, version 0.06, 2015-11-06");
const std::string cVersionStringGenerator("feed-merger v0.06");

void showVersion()
{
  std::cout << cVersionString << std::endl;
}

void showHelp()
{
  std::cout << "\nfeed-merger [URL ...]" << std::endl
            << "options:" << std::endl
            << "  --help        - displays this help message and quits" << std::endl
            << "  -?            - same as --help" << std::endl
            << "  --version     - displays the version of the program and quits" << std::endl
            << "  -v            - same as --version" << std::endl
            << "  --output FILE - specify the file name for the merged feed. Defaults to" << std::endl
            << "                  " << cDefaultOutputFileName << ", if not specified." << std::endl
            << "  -o FILE       - same as --output" << std::endl
            << "  URL           - URL of an RSS 2.0 feed that shall be merged. Can be repeated" << std::endl
            << "                  multiple times to specify several feeds." << std::endl;
}

int main(int argc, char** argv)
{
  std::unordered_set<std::string> feedURLs;
  std::string outputFileName;

  if ((argc > 1) and (argv != nullptr))
  {
    int i = 1;
    while (i<argc)
    {
      if (argv[i] != nullptr)
      {
        const std::string param = std::string(argv[i]);
        //help parameter
        if ((param == "--help") or (param == "-?") or (param == "/?"))
        {
          showHelp();
          return 0;
        }//help
        //version information requested?
        else if ((param == "--version") or (param == "-v"))
        {
          showVersion();
          return 0;
        } //version
        //output file name
        else if ((param == "--output") or (param == "-o"))
        {
          if (!outputFileName.empty())
          {
            std::cout << "Error: Output file name was already set!" << std::endl;
            return rcInvalidParameter;
          } //if name was already set
          if (argc <= i+1)
          {
            std::cout << "Error: No file name was given after " << param << "!" << std::endl;
            return rcInvalidParameter;
          }
          if (argv[i+1] == nullptr)
          {
            std::cout << "Error: No file name was given after " << param << "!" << std::endl;
            return rcInvalidParameter;
          }
          outputFileName = std::string(argv[i+1]);
          ++i; //Skip next parameter, because that is the file name we processed here.
        } //output file name
        //URL for next feed?
        else if ((param.substr(0, 7) == "http://")
                or (param.substr(0, 8) == "https://")
                or (param.substr(0, 6) == "ftp://"))
        {
          if (feedURLs.find(param) != feedURLs.end())
          {
            std::cout << "Error: feed URL " << param
                      << " was given more than once!" << std::endl;
            return rcInvalidParameter;
          }
          feedURLs.insert(param);
        } //URL
        else
        {
          //unknown or wrong parameter
          std::cout << "Invalid parameter given: \"" << param << "\"." << std::endl
                    << "Use --help to get a list of valid parameters." << std::endl;
          return rcInvalidParameter;
        } //if unknown parameter
      } //if parameter exists
      else
      {
        std::cout << "Parameter at index " << i << " is NULL." << std::endl;
        return rcInvalidParameter;
      }
      ++i;//on to next parameter
    } //while
  } //if arguments present

  //Are there any feeds at all?
  if (feedURLs.empty())
  {
    std::cout << "Error: No feeds are specified. See valid options by typing "
              << std::endl << "    " << argv[0] << " --help" << std::endl
              << "on the command line shell." << std::endl;
    return rcInvalidParameter;
  }
  //One feed is useless, no merge required.
  if (feedURLs.size() == 1)
  {
    std::cout << "Error: You specified just one feed, but at least two feeds "
              << "are needed to perform a merge." << std::endl;
    return rcInvalidParameter;
  }

  //Check, whether output file name was set.
  if (outputFileName.empty())
  {
    std::cout << "Info: Output file name will be set to " << cDefaultOutputFileName
              << ", because no file name was specified." << std::endl;
    outputFileName = cDefaultOutputFileName;
  }

  std::vector<std::string> feedSources;

  //Get all the feeds via cURL.
  for (auto item : feedURLs)
  {
    Curly cURL;
    cURL.setURL(item);
    //Allow cURL to follow redirects, ...
    cURL.followRedirects(true);
    /* ... but only up to three. That should be more than enough for most
       sanely configured servers and avoids endless redirect loops. */
    cURL.setMaximumRedirects(3);
    std::string sourceOfFeed;
    if (!cURL.perform(sourceOfFeed))
    {
      std::cout << "Error: Unable to retrieve feed from " << item << "!"
                << std::endl;
      return rcNetworkError;
    } //if
    if (cURL.getResponseCode() != 200)
    {
      std::cout << "Error: Retrieving feed from " << item << " returned "
                << "unexpected response code " << cURL.getResponseCode()
                << ". Expected: 200." << std::endl;
      return rcNetworkError;
    }
    if (sourceOfFeed.empty())
    {
      std::cout << "Error: Getting URL " << item << " returned empty result!"
                << std::endl;
      return rcNetworkError;
    }
    feedSources.push_back(sourceOfFeed);
  } //for

  //Parse feed sources into RSS 2.0 feeds.
  /* TODO: Support Atom feeds, too! */

  std::vector<RSS20::Channel> feeds;
  std::vector<std::string>::const_iterator feedSrcIter = feedSources.begin();
  while (feedSrcIter != feedSources.end())
  {
    RSS20::Channel feed;
    #ifdef DEBUG
    std::cout << "Parsing feed ..." << std::endl;
    #endif // DEBUG
    if (!RSS20::Parser::fromString(*feedSrcIter, feed))
    {
      std::cout << "Error: Could not parse the data from one feed as RSS 2.0!"
                << std::endl;
      return rcParserError;
    }
    feeds.push_back(feed);
    ++feedSrcIter;
  } //while

  std::vector<RSS20::Item> totalItems;
  std::vector<RSS20::Channel>::const_iterator feedIter = feeds.begin();
  while (feedIter != feeds.end())
  {
    std::vector<RSS20::Item>::size_type i;
    for (i = 0; i < feedIter->items().size(); ++i)
    {
      totalItems.push_back(feedIter->items().at(i));
    } //for i
    ++feedIter;
  } //while

  //sort items
  std::sort(totalItems.begin(), totalItems.end());

  //create merged feed object
  RSS20::Channel mergedFeed;
  /* Title, link and description are required attributes. */
  mergedFeed.setTitle("Merged feed (composed from " + intToString(feeds.size()) + " individual feeds)");
  //set placeholder for link
  mergedFeed.setLink("http:///dev/null");
  //set placeholder for title
  mergedFeed.setDescription("This feed was created by merging items of several feeds into one feed.");
  //Set name of generator.
  mergedFeed.setGenerator(cVersionStringGenerator);
  //Set the items.
  for (const auto & fi : totalItems)
  {
    mergedFeed.addItem(fi);
  } //for

  //Write merged feed to a file.
  if (!RSS20::Writer::toFile(mergedFeed, outputFileName))
  {
    std::cout << "Error: Could not write feed to " << outputFileName << "!" << std::endl;
    return rcFileError;
  }

  //Feed was written to file, we are done here.
  return 0;
}
