//---------------------------------------------------------------------------
/*
BeerWanter. A simple game.
Copyright (C) 2005-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From hhtp://www.richelbilderbeek.nl/GameBeerWanter.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include <Wt/WApplication>
#include <Wt/WContainerWidget>

#include "wtautoconfig.h"
#include "wtbeerwanterwidget.h"
#pragma GCC diagnostic pop

namespace ribi {

struct WtBeerWanterApplication : public Wt::WApplication
{
  WtBeerWanterApplication(const Wt::WEnvironment& env)
  : Wt::WApplication(env),
    m_widget(new WtBeerWanterWidget)
  {
    this->setTitle("BeerWanter");
    root()->addWidget(m_widget);
  }
  WtBeerWanterApplication(const WtBeerWanterApplication&) = delete;
  WtBeerWanterApplication& operator=(const WtBeerWanterApplication&) = delete;
  private:
  WtBeerWanterWidget * const m_widget;
  void OnLevelUp();
};

} //~namespace ribi

Wt::WApplication * createApplication(const Wt::WEnvironment& env)
{
  return new ribi::WtBeerWanterApplication(env);
}

int main(int argc, char **argv)
{
  ribi::WtAutoConfig a(argc,argv,createApplication);
  ribi::WtAutoConfig::SaveDefaultStylesheet();
  return a.Run();
  //return WRun(argc, argv, &createApplication);
}

