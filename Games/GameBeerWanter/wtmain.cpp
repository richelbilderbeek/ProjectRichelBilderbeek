//---------------------------------------------------------------------------
/*
BeerWanter. A simple game.
Copyright (C) 2005-2010 Richel Bilderbeek

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
#include <Wt/WApplication>
//---------------------------------------------------------------------------
#include "beerwanterwtwidget.h"
//---------------------------------------------------------------------------
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
//---------------------------------------------------------------------------
struct BeerWanterWtApplication : public Wt::WApplication
{
  BeerWanterWtApplication(const Wt::WEnvironment& env)
  : Wt::WApplication(env),
    m_widget(new BeerWanterWtWidget)
  {
    this->setTitle("BeerWanter");
    root()->addWidget(m_widget);
  }
  private:
  BeerWanterWtWidget * const m_widget;
  void OnLevelUp();
};
//---------------------------------------------------------------------------
Wt::WApplication * createApplication(const Wt::WEnvironment& env)
{
  return new BeerWanterWtApplication(env);
}
//---------------------------------------------------------------------------
int main(int argc, char **argv)
{
  return WRun(argc, argv, &createApplication);
}
//---------------------------------------------------------------------------
