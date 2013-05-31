//---------------------------------------------------------------------------
/*
TestTicTacToe, tool to test the TicTacToe class
Copyright (C) 2010 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestTicTacToe.htm
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WEnvironment>
#include <Wt/WEvent>
#include <Wt/WPushButton>
#include <Wt/WMessageBox>
//---------------------------------------------------------------------------
#include "../../Classes/CppWtTicTacToeWidget/wttictactoewidget.h"
//---------------------------------------------------------------------------
struct WtTicTacToeDialog : public Wt::WContainerWidget
{
  WtTicTacToeDialog()
  : m_button_about(new Wt::WPushButton),
    m_button_restart(new Wt::WPushButton),
    m_tictactoe(new WtTicTacToeWidget)
  {
    this->addWidget(m_tictactoe);
    this->addWidget(new Wt::WBreak(this));
    this->addWidget(m_button_restart);
    this->addWidget(m_button_about);
    m_button_about->setText("About");
    m_button_restart->setText("Restart");
    m_tictactoe->m_signal_state_changed.connect(
      boost::bind(
        &WtTicTacToeDialog::OnStateChanged,
        this));
    m_button_about->clicked().connect(
      this,&WtTicTacToeDialog::OnAbout);
    m_button_restart->clicked().connect(
      this,&WtTicTacToeDialog::OnRestart);
  }
  const std::string GetVersion()
  {
    return "1.2";
  }
  static const std::vector<std::string> GetVersionHistory()
  {
    std::vector<std::string> v;
    v.push_back("YYYY-MM-DD: version X.Y: [description]");
    v.push_back("2011-01-06: version 1.2: initial version");
    return v;
  }
  private:
  Wt::WPushButton * const m_button_about;
  Wt::WPushButton * const m_button_restart;
  WtTicTacToeWidget * const m_tictactoe;
  void OnAbout()
  {
    Wt::WMessageBox::show(
      Wt::WString("ToolTestTicTacToe (C) 2010 Richel Bilderbeek"),
      Wt::WString("From http://www.richelbilderbeek.nl/ToolTestTicTacToe.htm"),
      Wt::Ok);
  }
  void OnRestart()
  {
    m_tictactoe->Restart();
  }
  void OnStateChanged()
  {
    switch (m_tictactoe->GetState())
    {
      case TicTacToe::player1:
        m_button_restart->setText("Player 1 has won. Click to restart");
        break;
      case TicTacToe::player2:
        m_button_restart->setText("Player 2 has won. Click to restart");
        break;
      case TicTacToe::draw:
        m_button_restart->setText("Draw. Click to restart");
        break;
      case TicTacToe::no_winner:
        m_button_restart->setText("Restart");
        break;
      default:
        assert(!"Should not get here");
        break;
    }
  }
};
//---------------------------------------------------------------------------
struct WtApplication : public Wt::WApplication
{
  WtApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env),
    m_dialog(new WtTicTacToeDialog)
  {
    this->setTitle("ToolTestTicTacToe");
    root()->addWidget(m_dialog);
  }
  private:
  WtTicTacToeDialog * const m_dialog;
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
  return WRun(argc, argv, &createApplication);
}
//---------------------------------------------------------------------------
