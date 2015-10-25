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

#include <iostream>
#include <string>
#include <unordered_set>

//Return code that indicates invalid command line arguments.
const int rcInvalidParameter = 1;

void showVersion()
{
  std::cout << "feed-merger, version 0.01, 2015-10-25" << std::endl;
}

void showHelp()
{
  std::cout << "\nfeed-merger [URL ...]" << std::endl
            << "options:" << std::endl
            << "  --help       - displays this help message and quits" << std::endl
            << "  -?           - same as --help" << std::endl
            << "  --version    - displays the version of the program and quits" << std::endl
            << "  -v           - same as --version" << std::endl
            << "  URL          - URL of an RSS 2.0 feed that shall be merged. Can be repeated" << std::endl
            << "                 multiple times to specify several feeds." << std::endl;
}

int main(int argc, char** argv)
{
  std::unordered_set<std::string> feedURLs;

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

  std::cout << "Not implemented yet!" << std::endl;
  return 0;
}
