//---------------------------------------------------------------------------
/*
TestShinyButton, tool to test the ShinyButton class
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestShinyButton.htm
//---------------------------------------------------------------------------
#include <boost/program_options.hpp>
#include <boost/signals2.hpp>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WEnvironment>
#include <Wt/WPaintDevice>
#include <Wt/WPaintedWidget>
#include <Wt/WPainter>
#include <Wt/WPushButton>
#include <Wt/WFileResource>
//---------------------------------------------------------------------------
#include "wtautoconfig.h"
#include "wtshinybuttonwidget.h"
//---------------------------------------------------------------------------
struct WtApplication : public Wt::WApplication
{
  WtApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env),
    m_dialog(new WtTestShinyButtonMenuDialog)
  {
    this->setTitle("TestShinyButton");
    this->useStyleSheet("wt.css");
    root()->addWidget(m_dialog);
  }
  private:
  WtTestShinyButtonMenuDialog * const m_dialog;
};
//---------------------------------------------------------------------------
Wt::WApplication *createApplication(
  const Wt::WEnvironment& env)
{
  return new WtApplication(env);
}
//---------------------------------------------------------------------------
int main(int argc, char **argv)
{
  WtAutoConfig a(argc,argv,createApplication);
  WtAutoConfig::SaveDefaultStylesheet();
  boost::shared_ptr<WtShinyButtonWidget> w(new WtShinyButtonWidget(0.5,1.0,"TEST"));
  //w->
  return a.Run();
}
//---------------------------------------------------------------------------
