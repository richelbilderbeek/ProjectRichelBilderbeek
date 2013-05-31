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
///Need to #undef NDEBUG because Wt requires to #define DNDEBUG
#undef NDEBUG
//---------------------------------------------------------------------------
WtNsanaBrosGameDialog::WtNsanaBrosGameDialog()
  : m_dialog(new NsanaBrosGameDialog),
    m_area_widget(new WtNsanaBrosGameAreaWidget),
    m_keys_widget(new WtNsanaBrosKeysWidget)
{
  this->setContentAlignment(Wt::AlignCenter);
  ShowGame();
}
//---------------------------------------------------------------------------
void WtNsanaBrosGameDialog::OnCloseClick()
{
  m_signal_close();
}
//---------------------------------------------------------------------------
void WtNsanaBrosGameDialog::ShowGame()
{
  this->clear();
  //Title
  {
    Wt::WLabel * const title = new Wt::WLabel("Game");
    title->setStyleClass("title");
    this->addWidget(title);
  }
  this->addWidget(new Wt::WBreak);
  //GameArea
  this->addWidget(m_area_widget);
  this->addWidget(new Wt::WBreak);
  //Keys
  this->addWidget(m_keys_widget);
  this->addWidget(new Wt::WBreak);
  //Close button
  {
    Wt::WPushButton * const button = new Wt::WPushButton("Close");
    button->clicked().connect(
      this, &WtNsanaBrosGameDialog::OnCloseClick);
    this->addWidget(button);
  }
}
//---------------------------------------------------------------------------
