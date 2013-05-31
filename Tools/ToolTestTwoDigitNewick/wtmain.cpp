//---------------------------------------------------------------------------
/*
WtTestTwoDigitNewickDialog, Wt dialog to test the TwoDigitNewick class
Copyright (C) 2010-2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestTwoDigitNewick.htm
//---------------------------------------------------------------------------
#include <boost/program_options.hpp>
//---------------------------------------------------------------------------
#include <Wt/WApplication>
//---------------------------------------------------------------------------
#include "wttesttwodigitnewickdialog.h"
#include "wtaboutdialog.h"
//---------------------------------------------------------------------------
struct WtTestTwoDigitNewickApplication : public Wt::WApplication
{
  WtTestTwoDigitNewickApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
  {
    this->useStyleSheet("wt.css");
    this->setTitle("TestTwoDigitNewick");
    ShowMain();
  }
  void ShowMain()
  {
    WtTestTwoDigitNewickDialog * const d
      = new WtTestTwoDigitNewickDialog;

    d->m_signal_about.connect(
      boost::bind(
      &WtTestTwoDigitNewickApplication::ShowAbout,
      this));

    root()->clear();
    root()->addWidget(d);

  }
  void ShowAbout()
  {
    WtAboutDialog * const d
      = new WtAboutDialog(
        WtTestTwoDigitNewickDialog::GetAbout());

    d->m_signal_close.connect(
      boost::bind(
      &WtTestTwoDigitNewickApplication::ShowMain,
      this));

    root()->clear();
    root()->addWidget(d);

  }
};
//---------------------------------------------------------------------------
Wt::WApplication *createApplication(
  const Wt::WEnvironment& env)
{
  return new WtTestTwoDigitNewickApplication(env);
}
//---------------------------------------------------------------------------
int main(int argc, char **argv)
{

  boost::program_options::options_description d(
    "Allowed options for TestTwoDigitNewick");
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
      argc, argv, d), m);
  boost::program_options::notify(m);

  if (m.count("help"))
  {
    //Display the options_description
    std::cout << d << "\n";
    return 0;
  }

  //Create the arguments in std::string format
  std::vector<std::string> v(7);
  v[0] = argv[0];
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
  return WRun(w.size(), &w[0], &createApplication);
}
//---------------------------------------------------------------------------
