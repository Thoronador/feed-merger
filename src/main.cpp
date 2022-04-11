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

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include "Curly.hpp"
#include "rss2.0/Channel.hpp"
#include "rss2.0/Merger.hpp"
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
//Return code that a merge error.
const int rcMergeError = 5;

//The default output file name that is used if no file name is given.
const std::string cDefaultOutputFileName = "merged-feeds.xml";

//strings that indicate the program's version
const std::string cVersionString( "feed-merger, version 0.08, 2022-04-11");
const std::string cVersionStringGenerator("feed-merger v0.08");

void showVersion()
{
  std::cout << cVersionString << std::endl;
}

void showHelp()
{
  std::cout << "\nfeed-merger [URL ...] [-o FILE]" << std::endl
            << "options:" << std::endl
            << "  URL           - URL of an RSS 2.0 feed that shall be merged. Can be repeated" << std::endl
            << "                  multiple times to specify several feeds." << std::endl
            << "  --output FILE - specify the file name for the merged feed. Defaults to" << std::endl
            << "                  " << cDefaultOutputFileName << ", if not specified." << std::endl
            << "  -o FILE       - same as --output" << std::endl
            << "  --help        - displays this help message and quits" << std::endl
            << "  -?            - same as --help" << std::endl
            << "  --version     - displays the version of the program and quits" << std::endl
            << "  -v            - same as --version" << std::endl;
}

int main(int argc, char** argv)
{
  std::unordered_set<std::string> feedURLs;
  std::string outputFileName;

  if ((argc > 1) and (argv != nullptr))
  {
    int i = 1;
    while (i < argc)
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
            std::cerr << "Error: Output file name was already set!" << std::endl;
            return rcInvalidParameter;
          } //if name was already set
          if (argc <= i+1)
          {
            std::cerr << "Error: No file name was given after " << param << "!" << std::endl;
            return rcInvalidParameter;
          }
          if (argv[i+1] == nullptr)
          {
            std::cerr << "Error: No file name was given after " << param << "!" << std::endl;
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
            std::cerr << "Error: feed URL " << param
                      << " was given more than once!" << std::endl;
            return rcInvalidParameter;
          }
          feedURLs.insert(param);
        } //URL
        else
        {
          //unknown or wrong parameter
          std::cerr << "Invalid parameter given: \"" << param << "\"." << std::endl
                    << "Use --help to get a list of valid parameters." << std::endl;
          return rcInvalidParameter;
        } //if unknown parameter
      } //if parameter exists
      else
      {
        std::cerr << "Parameter at index " << i << " is NULL." << std::endl;
        return rcInvalidParameter;
      }
      ++i;//on to next parameter
    } //while
  } //if arguments present

  //Are there any feeds at all?
  if (feedURLs.empty())
  {
    std::cerr << "Error: No feeds are specified. See valid options by typing "
              << std::endl << "    " << argv[0] << " --help" << std::endl
              << "on the command line shell." << std::endl;
    return rcInvalidParameter;
  }
  //One feed is useless, no merge required.
  if (feedURLs.size() == 1)
  {
    std::cerr << "Error: You specified just one feed, but at least two feeds "
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
  for (const auto & item : feedURLs)
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
      std::cerr << "Error: Unable to retrieve feed from " << item << "!"
                << std::endl;
      return rcNetworkError;
    } //if
    if (cURL.getResponseCode() != 200)
    {
      std::cerr << "Error: Retrieving feed from " << item << " returned "
                << "unexpected response code " << cURL.getResponseCode()
                << ". Expected: 200." << std::endl;
      return rcNetworkError;
    }
    if (sourceOfFeed.empty())
    {
      std::cerr << "Error: Getting URL " << item << " returned empty result!"
                << std::endl;
      return rcNetworkError;
    }
    feedSources.push_back(sourceOfFeed);
  } //for

  //Parse feed sources into RSS 2.0 feeds.
  /* TODO: Support Atom feeds, too! */

  std::vector<RSS20::Channel> feeds;
  for (const auto & feedSrc : feedSources)
  {
    RSS20::Channel feed;
    #ifdef DEBUG
    std::cout << "Parsing feed ..." << std::endl;
    #endif // DEBUG
    if (!RSS20::Parser::fromString(feedSrc, feed))
    {
      std::cerr << "Error: Could not parse the data from one feed as RSS 2.0!"
                << std::endl;
      return rcParserError;
    }
    feeds.push_back(feed);
  } //for

  //create merged feed object
  RSS20::Channel mergedFeed;
  if (!RSS20::Merger::merge(feeds, mergedFeed))
  {
    std::cout << "Something wet wrong while merging the feeds!" << std::endl;
    return rcMergeError;
  }
  //Set name of generator.
  mergedFeed.setGenerator(cVersionStringGenerator);
  //sort items
  auto allItems = mergedFeed.items();
  std::sort(allItems.begin(), allItems.end(), std::greater<RSS20::Item>());
  mergedFeed.setItems(allItems);

  //Write merged feed to a file.
  if (!RSS20::Writer::toFile(mergedFeed, outputFileName))
  {
    std::cerr << "Error: Could not write feed to " << outputFileName << "!" << std::endl;
    return rcFileError;
  }

  //Feed was written to file, we are done here.
  return 0;
}
