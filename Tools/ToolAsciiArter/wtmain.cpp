//---------------------------------------------------------------------------
/*
TestAsciiArter, tool to test the AsciiArter class
Copyright (C) 2006-2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestAsciiArter.htm
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
//---------------------------------------------------------------------------
#include "wtautoconfig.h"
#include "wttestasciiarterdialog.h"
//---------------------------------------------------------------------------
#include <QFile>
//---------------------------------------------------------------------------
struct WtApplication : public Wt::WApplication
{
  WtApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env),
    m_dialog(new WtTestAsciiArterDialog)
  {
    this->setTitle("TestAsciiArter");
    this->useStyleSheet("wt.css");
    root()->addWidget(m_dialog);
  }
  private:
  WtTestAsciiArterDialog * const m_dialog;
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
  if (!QFile::exists("RichelbilderbeekNlBackground.png"))
  {
    QFile file(":/images/RichelbilderbeekNlBackground.png");
    file.copy("RichelbilderbeekNlBackground.png");
  }

  WtAutoConfig a(argc,argv,createApplication);
  WtAutoConfig::SaveDefaultStylesheet();
  return a.Run();
}
//---------------------------------------------------------------------------
