//---------------------------------------------------------------------------
#include <cassert>
#include <cstdlib>
//---------------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
#include <boost/cast.hpp>
//---------------------------------------------------------------------------
#include <Wt/WBreak>
#include <Wt/WButtonGroup>
#include <Wt/WGroupBox>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WRadioButton>
#include <Wt/WPushButton>
//---------------------------------------------------------------------------
#include "about.h"
#include "trace.h"
#include "wtaboutdialog.h"
#include "wtpaperrockscissorsdialog.h"
#include "wtpaperrockscissorsdialogstate.h"
#include "wtpaperrockscissorsserver.h"
//---------------------------------------------------------------------------
WtPaperRockScissorsDialogState::WtPaperRockScissorsDialogState(
  WtPaperRockScissorsDialog * const dialog,
  WtPaperRockScissorsServer * const server)
  : m_dialog(dialog),
    m_server(server)
{
  assert(m_dialog);
  assert(m_server);
}
//---------------------------------------------------------------------------
WtPaperRockScissorsDialogState::~WtPaperRockScissorsDialogState()
{
  Disconnect();
}
//---------------------------------------------------------------------------
void WtPaperRockScissorsDialogState::Connect()
{
  if (!m_dialog->m_event_connection.connected())
  {
    m_dialog->m_event_connection
      = m_server->ChangeIndexEvent().connect(m_dialog,
        &WtPaperRockScissorsDialog::ServerEvent);
  }
}
//---------------------------------------------------------------------------
void WtPaperRockScissorsDialogState::Disconnect()
{
  //Stop listing to events
  if (m_dialog->m_event_connection.connected())
  {
    m_dialog->m_event_connection.disconnect();
  }
}
//---------------------------------------------------------------------------
void WtPaperRockScissorsDialogState::SetStateAbout(const WtPaperRockScissorsDialogState * const prev_state)
{
  WtPaperRockScissorsDialogStateAbout * about
    = boost::polymorphic_downcast<
        WtPaperRockScissorsDialogStateAbout*
      >(m_dialog->GetStateAbout());
  assert(about);
  about->SetOnCloseState(prev_state);
  m_dialog->SetState(about);
}
//---------------------------------------------------------------------------
WtPaperRockScissorsDialogStateAbout::WtPaperRockScissorsDialogStateAbout(
  WtPaperRockScissorsDialog * const dialog,
  WtPaperRockScissorsServer * const server,
  WtPaperRockScissorsDialogState * const prev_state)
  : WtPaperRockScissorsDialogState(dialog,server),
    m_prev_state(prev_state)
{
  assert(m_dialog);
  assert(m_server);
  assert(prev_state);
}
//---------------------------------------------------------------------------
void WtPaperRockScissorsDialogStateAbout::ProcessEvent(const WtPaperRockScissorsEvent& event)
{
  //Do nothing :-)
}
//---------------------------------------------------------------------------
void WtPaperRockScissorsDialogStateAbout::OnClose()
{
  m_dialog->SetState(m_prev_state);
}
//---------------------------------------------------------------------------
void WtPaperRockScissorsDialogStateAbout::SetOnCloseState(WtPaperRockScissorsDialogState * const prev_state)
{
  assert(prev_state);
  m_prev_state = prev_state;
}
//---------------------------------------------------------------------------
void WtPaperRockScissorsDialogStateAbout::Show()
{
  //Temporarily do not listen to events
  Disconnect();

  About a = WtPaperRockScissorsDialog::GetAbout();
  WtAboutDialog * const d = new WtAboutDialog(a);
  TRACE("TODO");
  d->m_signal_close.connect(
    boost::bind(
    &WtPaperRockScissorsDialogStateAbout::OnClose,
    this));
  m_dialog->clear();
  m_dialog->addWidget(d);
}
//---------------------------------------------------------------------------
WtPaperRockScissorsDialogStateConnect::WtPaperRockScissorsDialogStateConnect(
  WtPaperRockScissorsDialog * const dialog,
  WtPaperRockScissorsServer * const server)
  : WtPaperRockScissorsDialogState(dialog,server)
{
  assert(m_dialog);
}
//---------------------------------------------------------------------------
void WtPaperRockScissorsDialogStateConnect::ProcessEvent(const WtPaperRockScissorsEvent& event)
{

}
//---------------------------------------------------------------------------
void WtPaperRockScissorsDialogStateConnect::Show()
{
  Connect();
}
//---------------------------------------------------------------------------
WtPaperRockScissorsDialogStateGame::WtPaperRockScissorsDialogStateGame(
  WtPaperRockScissorsDialog * const dialog,
  WtPaperRockScissorsServer * const server)
  : WtPaperRockScissorsDialogState(dialog,server)
{
  assert(m_dialog);
}
//---------------------------------------------------------------------------
void WtPaperRockScissorsDialogStateGame::ProcessEvent(const WtPaperRockScissorsEvent& event)
{

}
//---------------------------------------------------------------------------
///Send the new selected radio button's index
void WtPaperRockScissorsDialogStateGame::Send()
{
  m_server->SendMessageToServer(std::rand());
}
//---------------------------------------------------------------------------
void WtPaperRockScissorsDialogStateGame::Show()
{
  m_dialog->clear();
  //Title
  {
    Wt::WLabel * const title = new Wt::WLabel("PaperRockScissors");
    title->setStyleClass("title");
    m_dialog->addWidget(title);
  }
  //ButtonGroup
  {
    Wt::WGroupBox * const container = new Wt::WGroupBox("Which option?",m_dialog);
    m_group = new Wt::WButtonGroup(m_dialog);

    {
      Wt::WRadioButton * const button = new Wt::WRadioButton("A", container);
      new Wt::WBreak(container);
      m_group->addButton(button,0);
    }
    {
      Wt::WRadioButton * const button = new Wt::WRadioButton("B", container);
      new Wt::WBreak(container);
      m_group->addButton(button,1);
    }
    {
      Wt::WRadioButton * const button = new Wt::WRadioButton("C", container);
      new Wt::WBreak(container);
      m_group->addButton(button,2);
    }

    m_group->setSelectedButtonIndex(0);
      //m_server->GetCurrentIndex());
    m_group->checkedChanged().connect(
      this,&WtPaperRockScissorsDialogStateGame::Send);
  }
  //About
  {
    Wt::WPushButton * button = new Wt::WPushButton("About");
    m_dialog->addWidget(button);
    button->clicked().connect(this, &WtPaperRockScissorsDialogState::SetStateAbout);
  }
}
//---------------------------------------------------------------------------
WtPaperRockScissorsDialogStateLogin::WtPaperRockScissorsDialogStateLogin(
  WtPaperRockScissorsDialog * const dialog,
  WtPaperRockScissorsServer * const server)
  : WtPaperRockScissorsDialogState(dialog,server)
{
  assert(m_dialog);
}
//---------------------------------------------------------------------------
void WtPaperRockScissorsDialogStateLogin::ProcessEvent(const WtPaperRockScissorsEvent& event)
{

}
//---------------------------------------------------------------------------
void WtPaperRockScissorsDialogStateLogin::OnEditChanged()
{

}
//---------------------------------------------------------------------------
void WtPaperRockScissorsDialogStateLogin::Show()
{
  m_dialog->clear();
  //Title
  {
    Wt::WLabel * const title = new Wt::WLabel("PaperRockScissors login");
    title->setStyleClass("title");
    m_dialog->addWidget(title);
  }
  m_dialog->addWidget(new Wt::WBreak);
  //Label
  {
    Wt::WLabel * const label_login = new Wt::WLabel("Login name:");
    m_dialog->addWidget(label_login);
  }
  //m_edit_username
  {
    m_edit_username = new Wt::WLineEdit(
      boost::lexical_cast<std::string>(
        std::rand()));
    m_edit_username->changed().connect(
      this,&WtPaperRockScissorsDialogStateLogin::OnEditChanged);
    m_dialog->addWidget(m_edit_username);
  }
  m_dialog->addWidget(new Wt::WBreak);
  //About
  {
    Wt::WPushButton * button = new Wt::WPushButton("About");
    m_dialog->addWidget(button);
    button->clicked().connect(this, &WtPaperRockScissorsDialogState::SetStateAbout);
  }
}
//---------------------------------------------------------------------------
