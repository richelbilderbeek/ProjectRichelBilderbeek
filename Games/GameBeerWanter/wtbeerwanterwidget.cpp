#include "wtbeerwanterwidget.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
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

#include "beerwantermaindialog.h"
#pragma GCC diagnostic pop

ribi::WtBeerWanterWidget::WtBeerWanterWidget(
  Wt::WContainerWidget *parent)
  : Wt::WPaintedWidget(parent),
    m_debug_text{},
    m_dialog(new BeerWanterMainDialog(600,500,39,102,600,500)),
    m_image(new Wt::WPainter::Image("Beer.png",39,102))
{
  assert(m_image);
  this->resize(
    m_dialog->GetWindowWidth(),
    m_dialog->GetWindowHeight());
  this->mouseMoved().connect(this, &ribi::WtBeerWanterWidget::OnMouseMove);
  this->mouseWentDown().connect(this, &ribi::WtBeerWanterWidget::OnClick);
  this->update();
}

void ribi::WtBeerWanterWidget::OnClick(const Wt::WMouseEvent& /* e */)
{
  //No need to use 'e', because OnMouseMove updates the m_dialog its coordinats
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
  m_dialog->Click();
  this->update();
}

void ribi::WtBeerWanterWidget::OnMouseMove(const Wt::WMouseEvent& e)
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
  if (m_dialog->ClickWilBeSuccess())
  {
    m_debug_text += "-> CLICK WILL BE SUCCESS";
  }
  const int sprite_x = m_dialog->GetSpriteX();
  const int sprite_y = m_dialog->GetSpriteX();
  const int sprite_maxx = m_dialog->GetSpriteX() + m_dialog->GetSpriteWidth();
  const int sprite_maxy = m_dialog->GetSpriteY() + m_dialog->GetSpriteHeight();
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

  m_dialog->SetCursorPos(
    mouse_x,
    mouse_y);
  this->update();
}

void ribi::WtBeerWanterWidget::paintEvent(Wt::WPaintDevice *paintDevice)
{
  Wt::WPainter painter(paintDevice);
  //Display the current level
  painter.drawText(
    0,0,
    m_dialog->GetWindowWidth(),
    m_dialog->GetWindowHeight(),
    Wt::AlignCenter | Wt::AlignMiddle,
    boost::lexical_cast<std::string>(m_dialog->GetLevel()));
  //Display the sprite
  painter.drawImage(
    m_dialog->GetSpriteX(),
    m_dialog->GetSpriteY(),
    *m_image);
  //#define DEBUG_SHOW_GRID
  #ifdef DEBUG_SHOW_GRID
  for (int x = 0; x!= 600; x+=100)
    painter.drawLine(x,0,x,600);
  for (int y = 0; y!= 600; y+=100)
    painter.drawLine(0,y,600,y);
  #endif
}


