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
#ifndef WTPAPERROCKSCISSORSDIALOG_H
#define WTPAPERROCKSCISSORSDIALOG_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
//---------------------------------------------------------------------------
#include <boost/signals.hpp>
#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
#include "about.h"
//---------------------------------------------------------------------------
namespace Wt
{
  struct WApplication;
  struct WButtonGroup;
  struct WLabel;
  struct WPushButton;
}
//---------------------------------------------------------------------------
struct WtPaperRockScissorsDialogState;
struct WtPaperRockScissorsEvent;
struct WtPaperRockScissorsServer;
struct WtPaperRockScissorsDialogState;
//---------------------------------------------------------------------------
struct WtPaperRockScissorsDialog : public Wt::WContainerWidget
{
  typedef WtPaperRockScissorsDialogState State;
  WtPaperRockScissorsDialog(Wt::WContainerWidget *parent = 0);
  ~WtPaperRockScissorsDialog();

  State * GetStateAbout() const;
  State * GetStateConnect() const;
  State * GetStateGame() const;
  State * GetStateLogin() const;
  void SetState(State * const state);

  void Send();

  ///m_signal_close is emitted when program closes
  mutable boost::signals2::signal<void ()> m_signal_close;

  //Server has something to broadcast, called from another session
  void ServerEvent(const WtPaperRockScissorsEvent& event);

  ///connection to server
  boost::signals::connection m_event_connection;

private:
  Wt::WApplication * const m_application;
  WtPaperRockScissorsServer * const m_server;

  State * m_state;
  const boost::scoped_ptr<State> m_state_about;
  const boost::scoped_ptr<State> m_state_connect;
  const boost::scoped_ptr<State> m_state_login;
  const boost::scoped_ptr<State> m_state_game;

  void OnClose();
  void Show();

  public:
  static const std::vector<std::string> GetVersionHistory();
  static const std::string GetVersion();
  static const About GetAbout();

};
//---------------------------------------------------------------------------
#endif // WTPAPERROCKSCISSORSDIALOG_H
