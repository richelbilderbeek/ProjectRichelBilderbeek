#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtk3opeenrijselectplayerwidget.h"

#include <QMouseEvent>
#include <QPainter>

#include "qtk3opeenrijresources.h"
#pragma GCC diagnostic pop

const int ribi::QtK3OpEenRijSelectPlayerWidget::m_sprite_height = 50;
const int ribi::QtK3OpEenRijSelectPlayerWidget::m_sprite_width  = 50;

ribi::QtK3OpEenRijSelectPlayerWidget::QtK3OpEenRijSelectPlayerWidget(
  const boost::shared_ptr<const QtK3OpEenRijResources> resources,
  QWidget *parent)
  : QWidget(parent),
    m_is_player3_kathleen(false), //Set default to Josje
    m_is_player_human{},
    m_josje(resources->GetPlayersFilenames()[3].c_str() ),
    m_josje_grey( resources->GetPlayersGreyFilenames()[3].c_str() ),
    m_karen(resources->GetPlayersFilenames()[0].c_str() ),
    m_karen_grey( resources->GetPlayersGreyFilenames()[0].c_str() ),
    m_kathleen(resources->GetPlayersFilenames()[2].c_str() ),
    m_kathleen_grey( resources->GetPlayersGreyFilenames()[2].c_str() ),
    m_kristel(resources->GetPlayersFilenames()[1].c_str() ),
    m_kristel_grey( resources->GetPlayersGreyFilenames()[1].c_str() ),
    m_computer1(resources->GetComputersFilenames()[0].c_str() ),
    m_computer2(resources->GetComputersFilenames()[1].c_str() ),
    m_computer3(resources->GetComputersFilenames()[2].c_str() ),
    m_computer_grey(resources->GetComputerGreyFilename().c_str() )
{
  m_is_player_human[0] = true;
  m_is_player_human[1] = true;
  m_is_player_human[2] = true;


  this->setMinimumWidth( 3 * m_sprite_width );
  this->setMinimumHeight(3 * m_sprite_height);
  this->setMaximumWidth( 3 * m_sprite_width );
  this->setMaximumHeight(3 * m_sprite_height);
}

void ribi::QtK3OpEenRijSelectPlayerWidget::mousePressEvent(QMouseEvent * e)
{
  const int mouse_x = e->x();
  const int mouse_y = e->y();
  const int col_index = mouse_x / m_sprite_width;
  const int row_index = mouse_y / m_sprite_height;
  const bool was_human = m_is_player_human[row_index];
  const bool is_human = col_index == 0;
  m_is_player_human[row_index] = is_human;
  if (row_index == 2 && is_human && was_human) m_is_player3_kathleen = !m_is_player3_kathleen;
  this->repaint();
}

void ribi::QtK3OpEenRijSelectPlayerWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawImage(0 * m_sprite_width,0 * m_sprite_height,m_is_player_human[0] ? m_karen : m_karen_grey);
  painter.drawImage(0 * m_sprite_width,1 * m_sprite_height,m_is_player_human[1] ? m_kristel : m_kristel_grey);
  painter.drawImage(0 * m_sprite_width,2 * m_sprite_height,
    m_is_player_human[2]
      ?  m_is_player3_kathleen ? m_kathleen      : m_josje
      :  m_is_player3_kathleen ? m_kathleen_grey : m_josje_grey
    );
  painter.drawImage(1 * m_sprite_width,0 * m_sprite_height,m_is_player_human[0] ? m_computer_grey : m_computer1);
  painter.drawImage(1 * m_sprite_width,1 * m_sprite_height,m_is_player_human[1] ? m_computer_grey : m_computer2);
  painter.drawImage(1 * m_sprite_width,2 * m_sprite_height,m_is_player_human[2] ? m_computer_grey : m_computer3);
}

