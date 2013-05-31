//---------------------------------------------------------------------------
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include <Wt/WBreak>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WPushButton>
//---------------------------------------------------------------------------
#include "nsanabroswtheader.h"
//---------------------------------------------------------------------------
WtNsanaBrosOptionsDialog::WtNsanaBrosOptionsDialog()
  : m_dialog(new NsanaBrosOptionsDialog)
{
  this->setContentAlignment(Wt::AlignCenter);

  ShowOptions();
}
//---------------------------------------------------------------------------
void WtNsanaBrosOptionsDialog::OnCloseClick()
{
  m_signal_close();
}
//---------------------------------------------------------------------------
void WtNsanaBrosOptionsDialog::ShowOptions()
{
  this->clear();
  //Title
  {
    Wt::WLabel * const title = new Wt::WLabel("Options");
    title->setStyleClass("title");
    this->addWidget(title);
  }
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  //Close button
  {
    Wt::WPushButton * const button = new Wt::WPushButton("Close");
    button->clicked().connect(
      this, &WtNsanaBrosOptionsDialog::OnCloseClick);
    this->addWidget(button);
  }
}
//---------------------------------------------------------------------------
