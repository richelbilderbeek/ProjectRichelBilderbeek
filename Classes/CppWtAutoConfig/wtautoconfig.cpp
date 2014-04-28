//---------------------------------------------------------------------------
/*
WtAutoConfig, configures a Wt server in a default way
Copyright (C) 2011-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppWtAutoConfig.htm
//---------------------------------------------------------------------------
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/program_options.hpp>

#include <Wt/WApplication>
#include <Wt/WEnvironment>

#include "wtautoconfig.h"
#pragma GCC diagnostic pop

ribi::WtAutoConfig::WtAutoConfig(
  const int argc, char ** const argv,const FunctionType function)
  : m_argc(argc),
    m_argv(argv),
    m_function(function)
{

}

const std::string ribi::WtAutoConfig::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> ribi::WtAutoConfig::GetVersionHistory()
{
  return {
    "2011-04-16: version 1.0: initial version",
    "2011-04-18: version 1.1: added CreateDefaultStylesheet and SaveDefaultStylesheet methods"
  };
}

int ribi::WtAutoConfig::Run()
{
  // Declare the supported options.
  boost::program_options::options_description d(
    "Allowed options for TestLed");
  std::string docroot;
  std::string http_address;
  std::string http_port;
  d.add_options()
      ("help",
        "produce this help message")
      ("docroot",
         boost::program_options::value<std::string>(&docroot)->default_value("."),
         "the docroot")
      ("http-address",
         boost::program_options::value<std::string>(&http_address)->default_value("0.0.0.0"),
         "the server's http address")
      ("http-port",
         boost::program_options::value<std::string>(&http_port)->default_value("8080"),
         "the server's http port")
      ;

  boost::program_options::variables_map m;
  boost::program_options::store(
    boost::program_options::parse_command_line(
      m_argc, m_argv, d), m);
  boost::program_options::notify(m);

  if (m.count("help"))
  {
    //Display the options_description
    std::cout << d << "\n";
    return 0;
  }

  //Create the arguments in std::string format
  std::vector<std::string> v(7);
  v[0] = m_argv[0];
  v[1] = "--docroot";
  v[2] = docroot;
  v[3] = "--http-address";
  v[4] = http_address;
  v[5] = "--http-port";
  v[6] = http_port;

  //Convert the arguments to char* format
  std::vector<char*> w(7);
  for (int i=0; i!=7; ++i) w[i] = &v[i][0];

  //Give Wt the modified parameters
  return WRun(w.size(), &w[0], m_function);
}

const std::vector<std::string> ribi::WtAutoConfig::CreateDefaultStylesheet()
{
  std::vector<std::string> v;

  v.push_back("* { font-family:\"Courier New\"; }");
  v.push_back("");
  v.push_back("body");
  v.push_back("{");
  v.push_back("  background-image:url('RichelbilderbeekNlBackground.png');");
  v.push_back("  background-position:center center;");
  v.push_back("}");
  v.push_back("");
  v.push_back(".title");
  v.push_back("{");
  v.push_back("  font-weight:bold;");
  v.push_back("  font-size:xx-large;");
  v.push_back("}");
  v.push_back("");
  v.push_back("table, th, td");
  v.push_back("{");
  v.push_back("  border: 1px solid black;");
  v.push_back("}");
  v.push_back("");
  v.push_back("td");
  v.push_back("{");
  v.push_back("  padding:12px;");
  v.push_back("}");
  v.push_back("");
  v.push_back(".menu * .item");
  v.push_back("{");
  v.push_back("  cursor: pointer; cursor: hand;");
  v.push_back("  font-size:x-large;");
  v.push_back("  color: black;");
  v.push_back("  padding:12px;");
  v.push_back("}");
  v.push_back("");
  v.push_back(".menu * .itemselected {");
  v.push_back("  font-size:x-large;");
  v.push_back("  font-weight: bold;");
  v.push_back("  color: blue;");
  v.push_back("  padding:12px;");
  v.push_back("}");
  v.push_back("");
  v.push_back(".wtwebsitemenu * .item");
  v.push_back("{");
  v.push_back("  cursor: pointer; cursor: hand;");
  v.push_back("  font-size:small;");
  v.push_back("  color: black;");
  v.push_back("  padding:4px;");
  v.push_back("  background-color:rgb(160,160,160);");
  v.push_back("  border:0px");
  v.push_back("}");
  v.push_back("");
  v.push_back(".wtwebsitemenu * .itemselected {");
  v.push_back("  font-size:small;");
  v.push_back("  font-weight:bold;");
  v.push_back("  color: blue;");
  v.push_back("  padding:4px;");
  v.push_back("  background-color:rgb(196,196,196);");
  v.push_back("  border:0px");
  v.push_back("}");
  return v;
}

void ribi::WtAutoConfig::SaveDefaultStylesheet()
{
  const std::vector<std::string> v = CreateDefaultStylesheet();
  std::ofstream f("wt.css");
  std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
}

