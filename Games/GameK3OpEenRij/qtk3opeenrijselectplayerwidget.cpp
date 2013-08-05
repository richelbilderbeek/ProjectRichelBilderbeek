#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtk3opeenrijselectplayerwidget.h"

#include <QMouseEvent>
#include <QPainter>


const int QtK3OpEenRijSelectPlayerWidget::m_sprite_height = 50;
const int QtK3OpEenRijSelectPlayerWidget::m_sprite_width  = 50;

QtK3OpEenRijSelectPlayerWidget::QtK3OpEenRijSelectPlayerWidget(QWidget *parent)
  : QWidget(parent),
    m_player1(":/images/K3OpEenRijPlayer1.png"),
    m_player1_grey(":/images/K3OpEenRijPlayer1Grey.png"),
    m_player2(":/images/K3OpEenRijPlayer2.png"),
    m_player2_grey(":/images/K3OpEenRijPlayer2Grey.png"),
    m_player3(":/images/K3OpEenRijPlayer3.png"),
    m_player3_grey(":/images/K3OpEenRijPlayer3Grey.png"),
    m_computer1(":/images/K3OpEenRijComputer1.png"),
    m_computer2(":/images/K3OpEenRijComputer2.png"),
    m_computer3(":/images/K3OpEenRijComputer3.png"),
    m_computer_grey(":/images/K3OpEenRijComputerGrey.png")
{
  m_is_player_human[0] = true;
  m_is_player_human[1] = true;
  m_is_player_human[2] = true;

  this->setMinimumWidth( 2 * m_sprite_width );
  this->setMinimumHeight(3 * m_sprite_height);
  this->setMaximumWidth( 2 * m_sprite_width );
  this->setMaximumHeight(3 * m_sprite_height);
}

void QtK3OpEenRijSelectPlayerWidget::mousePressEvent(QMouseEvent * e)
{
  const int mouse_x = e->x();
  const int mouse_y = e->y();
  const int index = mouse_y / m_sprite_height;
  const bool is_human = ( mouse_x / m_sprite_width == 0);
  m_is_player_human[index] = is_human;
  this->repaint();
}

void QtK3OpEenRijSelectPlayerWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawImage(0 * m_sprite_width,0 * m_sprite_height,m_is_player_human[0] ? m_player1 : m_player1_grey);
  painter.drawImage(0 * m_sprite_width,1 * m_sprite_height,m_is_player_human[1] ? m_player2 : m_player2_grey);
  painter.drawImage(0 * m_sprite_width,2 * m_sprite_height,m_is_player_human[2] ? m_player3 : m_player3_grey);
  painter.drawImage(1 * m_sprite_width,0 * m_sprite_height,m_is_player_human[0] ? m_computer_grey : m_computer1);
  painter.drawImage(1 * m_sprite_width,1 * m_sprite_height,m_is_player_human[1] ? m_computer_grey : m_computer2);
  painter.drawImage(1 * m_sprite_width,2 * m_sprite_height,m_is_player_human[2] ? m_computer_grey : m_computer3);
}

