//---------------------------------------------------------------------------
/*
PaperRockScissors, time polling server
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
//From http://www.richelbilderbeek.nl/ToolPaperRockScissors.htm
//---------------------------------------------------------------------------
#ifndef WTPAPERROCKSCISSORSSERVER_H
#define WTPAPERROCKSCISSORSSERVER_H
//---------------------------------------------------------------------------
#include <boost/thread.hpp>
//#include <boost/timer.hpp>
//---------------------------------------------------------------------------
#include <Wt/WObject>
#include <Wt/WSignal>
#include <Wt/WTimer>
//---------------------------------------------------------------------------
#include "wtpaperrockscissorsevent.h"
//---------------------------------------------------------------------------
struct WtPaperRockScissorsServer : public Wt::WObject
{
  static WtPaperRockScissorsServer * GetInstance();

  void SendMessageToServer(const int message);
  Wt::Signal<WtPaperRockScissorsEvent>& ChangeIndexEvent() { return m_change_index_event; }

private:
  WtPaperRockScissorsServer();
  static boost::scoped_ptr<WtPaperRockScissorsServer> m_instance;

  Wt::Signal<WtPaperRockScissorsEvent> m_change_index_event;
  boost::mutex m_mutex;
};
//---------------------------------------------------------------------------
#endif // WTPAPERROCKSCISSORSSERVER_H
