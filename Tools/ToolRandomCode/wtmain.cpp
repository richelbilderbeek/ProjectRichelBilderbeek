//---------------------------------------------------------------------------
/*
RandomCodeWt, web application to generate random C++ code
Copyright (C) 2010-2011  Richel Bilderbeek

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
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolRandomCode.htm
//---------------------------------------------------------------------------
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
//---------------------------------------------------------------------------
#include "wtautoconfig.h"
#include "wtrandomcodemenudialog.h"
//---------------------------------------------------------------------------
struct WtRandomCodeApplication : public Wt::WApplication
{
  WtRandomCodeApplication(const Wt::WEnvironment& env)
  : Wt::WApplication(env)
  {
    this->setTitle("RandomCode");
    this->useStyleSheet("wt.css");
    root()->addWidget(new WtRandomCodeMenuDialog);
  }
};
//---------------------------------------------------------------------------
Wt::WApplication * createApplication(const Wt::WEnvironment& env)
{
  return new WtRandomCodeApplication(env);
}
//---------------------------------------------------------------------------
int main(int argc, char **argv)
{
  WtAutoConfig a(argc,argv,createApplication);
  WtAutoConfig::SaveDefaultStylesheet();
  return a.Run();
}
//---------------------------------------------------------------------------

