//---------------------------------------------------------------------------
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WFileResource>
#include <Wt/WImage>
#include <Wt/WLineEdit>
#include <Wt/WPainter>
#include <Wt/WPushButton>
#include <Wt/WResource>
#include <Wt/WText>
#include <Wt/WTextArea>
//---------------------------------------------------------------------------
#include "beerwanter.h"
#include "beerwanterwtwidget.h"
//Cannot use assert due to the following error:
//  http://richelbilderbeek.nl/CppCompileErrorCc1plusInternalCompilerErrorSegmentationFault.htm
//#define MY_NDEBUG to disable this Assert
#include "myassert.h"
//---------------------------------------------------------------------------
BeerWanterWtWidget::BeerWanterWtWidget(
  Wt::WContainerWidget *parent)
  : Wt::WPaintedWidget(parent),
    m_image(new Wt::WPainter::Image("Beer.png",39,102)),
    m_beerwanter(new BeerWanter(600,500,39,102,600,500))
{
  Assert(m_image);
  this->resize(
    m_beerwanter->GetWindowWidth(),
    m_beerwanter->GetWindowHeight());
  this->mouseMoved().connect(this, &BeerWanterWtWidget::OnMouseMove);
  this->mouseWentDown().connect(this, &BeerWanterWtWidget::OnClick);
  this->update();
}
//---------------------------------------------------------------------------
void BeerWanterWtWidget::OnClick(const Wt::WMouseEvent& e)
{
  #ifdef DEBUG_SHOW_MOUSE_CLICK_POSITION
  const int mouse_x = e.widget().x;
  const int mouse_y = e.widget().y;
  m_debug_text
    = "CLICK: ("
    + boost::lexical_cast<std::string>(mouse_x)
    + ","
    + boost::lexical_cast<std::string>(mouse_y)
    + ")";
  #endif
  m_beerwanter->Click();
  this->update();
}
//---------------------------------------------------------------------------
void BeerWanterWtWidget::OnMouseMove(const Wt::WMouseEvent& e)
{
  const int mouse_x = e.widget().x;
  const int mouse_y = e.widget().y;
  #ifdef DEBUG_SHOW_MOUSE_POSITION
  m_debug_text
    = "MOVE: ("
    + boost::lexical_cast<std::string>(mouse_x)
    + ","
    + boost::lexical_cast<std::string>(mouse_y)
    + ")";
  if (m_beerwanter->ClickWilBeSuccess())
  {
    m_debug_text += "-> CLICK WILL BE SUCCESS";
  }
  const int sprite_x = m_beerwanter->GetSpriteX();
  const int sprite_y = m_beerwanter->GetSpriteX();
  const int sprite_maxx = m_beerwanter->GetSpriteX() + m_beerwanter->GetSpriteWidth();
  const int sprite_maxy = m_beerwanter->GetSpriteY() + m_beerwanter->GetSpriteHeight();
  m_debug_text += ", Sprite: ("
    + boost::lexical_cast<std::string>(sprite_x)
    + ","
    + boost::lexical_cast<std::string>(sprite_y)
    + ")-("
    + boost::lexical_cast<std::string>(sprite_maxx)
    + ","
    + boost::lexical_cast<std::string>(sprite_maxy)
    + ")";
  #endif

  m_beerwanter->SetCursorPos(
    mouse_x,
    mouse_y);
  this->update();
}
//---------------------------------------------------------------------------
void BeerWanterWtWidget::paintEvent(Wt::WPaintDevice *paintDevice)
{
  Wt::WPainter painter(paintDevice);
  //Display the current level
  painter.drawText(
    0,0,
    m_beerwanter->GetWindowWidth(),
    m_beerwanter->GetWindowHeight(),
    Wt::AlignCenter | Wt::AlignMiddle,
    boost::lexical_cast<std::string>(m_beerwanter->GetLevel()));
  //Display the sprite
  painter.drawImage(
    m_beerwanter->GetSpriteX(),
    m_beerwanter->GetSpriteY(),
    *m_image);
  //#define DEBUG_SHOW_GRID
  #ifdef DEBUG_SHOW_GRID
  for (int x = 0; x!= 600; x+=100)
    painter.drawLine(x,0,x,600);
  for (int y = 0; y!= 600; y+=100)
    painter.drawLine(0,y,600,y);
  #endif
}
//---------------------------------------------------------------------------

