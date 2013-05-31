//---------------------------------------------------------------------------
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include <Wt/WBreak>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WPaintedWidget>
#include <Wt/WPushButton>
//---------------------------------------------------------------------------
#include "nsanabroswtheader.h"
//---------------------------------------------------------------------------
WtNsanaBrosMenuDialog::WtNsanaBrosMenuDialog()
  : m_dialog(new NsanaBrosMenuDialog)
{
  this->setContentAlignment(Wt::AlignCenter);

  ShowMenu();
}
//---------------------------------------------------------------------------
void WtNsanaBrosMenuDialog::OnAboutClick()
{
  ShowAbout();
}
//---------------------------------------------------------------------------
void WtNsanaBrosMenuDialog::OnCloseClick()
{
  m_signal_close();
}
//---------------------------------------------------------------------------
void WtNsanaBrosMenuDialog::OnOptionsClick()
{
  ShowOptions();
}
//---------------------------------------------------------------------------
void WtNsanaBrosMenuDialog::OnStartClick()
{
  ShowGame();
}
//---------------------------------------------------------------------------
void WtNsanaBrosMenuDialog::ShowAbout()
{
  About a = NsanaBrosMenuDialog::GetAbout();
  WtAboutDialog * const d = new WtAboutDialog(a);
  d->m_signal_close.connect(
    boost::bind(
    &WtNsanaBrosMenuDialog::ShowMenu,
    this));
  this->clear();
  this->addWidget(d);
}
//---------------------------------------------------------------------------
void WtNsanaBrosMenuDialog::ShowGame()
{
  WtNsanaBrosGameDialog * const d = new WtNsanaBrosGameDialog;
  d->m_signal_close.connect(
    boost::bind(
    &WtNsanaBrosMenuDialog::ShowMenu,
    this));
  this->clear();
  this->addWidget(d);
}
//---------------------------------------------------------------------------
void WtNsanaBrosMenuDialog::ShowMenu()
{
  this->clear();
  //Title
  {
    Wt::WLabel * const title = new Wt::WLabel("Super Nsana Bros");
    title->setStyleClass("title");
    this->addWidget(title);
  }
  this->addWidget(new Wt::WBreak);
  //Start button
  {
    Wt::WPushButton * const button = new Wt::WPushButton("Start");
    button->clicked().connect(
      this, &WtNsanaBrosMenuDialog::OnStartClick);
    this->addWidget(button);
  }
  this->addWidget(new Wt::WBreak);
  //Options button
  {
    Wt::WPushButton * const button = new Wt::WPushButton("Options");
    button->clicked().connect(
      this,&WtNsanaBrosMenuDialog::OnOptionsClick);
    this->addWidget(button);
  }
  this->addWidget(new Wt::WBreak);
  //About button
  {
    Wt::WPushButton * const button = new Wt::WPushButton("About");
    button->clicked().connect(
      this, &WtNsanaBrosMenuDialog::OnAboutClick);
    this->addWidget(button);
  }
  this->addWidget(new Wt::WBreak);
  //Close button
  {
    Wt::WPushButton * const button = new Wt::WPushButton("Close");
    button->clicked().connect(
      this, &WtNsanaBrosMenuDialog::OnCloseClick);
    this->addWidget(button);
  }
}
//---------------------------------------------------------------------------
void WtNsanaBrosMenuDialog::ShowOptions()
{
  WtNsanaBrosOptionsDialog * const d = new WtNsanaBrosOptionsDialog;
  d->m_signal_close.connect(
    boost::bind(
    &WtNsanaBrosMenuDialog::ShowMenu,
    this));
  this->clear();
  this->addWidget(d);
}
//---------------------------------------------------------------------------
