#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconnectthreewidget.h"

#include <QMouseEvent>
#include <QPainter>

#include "connectthree.h"
#include "connectthreemove.h"
#include "connectthreeresources.h"
#include "connectthreewidget.h"
#include "qtconnectthreeresources.h"
#pragma GCC diagnostic pop

const int ribi::con3::QtConnectThreeWidget::m_sprite_width  = 50;
const int ribi::con3::QtConnectThreeWidget::m_sprite_height = 50;

ribi::con3::QtConnectThreeWidget::QtConnectThreeWidget(
  const boost::shared_ptr<const ConnectThreeResources> resources,
  QWidget *parent,
  const std::bitset<3>& is_player_human,
  const int n_cols,
  const int n_rows)
  : QWidget(parent),
    m_signal_valid_move{},
    m_widget(new ConnectThreeWidget(is_player_human,n_cols,n_rows)),
    m_player1(resources->GetPlayersFilenames()[0].c_str()),
    m_player2(resources->GetPlayersFilenames()[1].c_str()),
    m_player3(resources->GetPlayersFilenames()[2].c_str()),
    m_empty(resources->GetEmptyFilename().c_str())
{
  this->setMinimumWidth( n_cols * m_sprite_width );
  this->setMinimumHeight(n_rows * m_sprite_height);
  this->setMaximumWidth( n_cols * m_sprite_width );
  this->setMaximumHeight(n_rows * m_sprite_height);
}

void ribi::con3::QtConnectThreeWidget::DoComputerTurn()
{
  assert(IsComputerTurn());
  m_widget->DoComputerMove();
  this->update();
}

ribi::con3::Player ribi::con3::QtConnectThreeWidget::GetActivePlayer() const noexcept
{
  return m_widget->GetGame()->GetActivePlayer();
}

const std::string ribi::con3::QtConnectThreeWidget::GetVersion() noexcept
{
  return "2.0";
}

const std::vector<std::string> ribi::con3::QtConnectThreeWidget::GetVersionHistory() noexcept
{
  return {
    "2011-01-10: version 1.0: initial version",
    "2011-04-20: version 2.0: Moved logic to ConnectThreeWidget"
  };
}

ribi::con3::Winner ribi::con3::QtConnectThreeWidget::GetWinner() const noexcept
{
  return m_widget->GetGame()->GetWinner();
}

bool ribi::con3::QtConnectThreeWidget::IsComputerTurn() const noexcept
{
  return m_widget->IsComputerTurn();
}

void ribi::con3::QtConnectThreeWidget::mousePressEvent(QMouseEvent * e)
{
  //Disable clicking if it's the AI's turn
  if (IsComputerTurn()) return;

  const int mouse_x = e->x();
  const int mouse_y = e->y();
  const int x = mouse_x / m_sprite_width;
  const int y = mouse_y / m_sprite_height;
  if (m_widget->CanSelect(x,y))
  {
    m_widget->Select(x,y);
    if (m_widget->CanDoMove())
    {
      m_widget->DoMove();
      this->update();
      m_signal_valid_move();
    }
  }
}

void ribi::con3::QtConnectThreeWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  const int n_rows = m_widget->GetGame()->GetRows();
  const int n_cols = m_widget->GetGame()->GetCols();
  for (int y = 0; y!=n_rows; ++y)
  {
    for (int x = 0; x!=n_cols; ++x)
    {
      painter.drawImage(
        x * m_sprite_width,
        y * m_sprite_height,
        GetImage(m_widget->GetGame()->GetSquare(x,y))
      );
    }
  }
}

const QImage& ribi::con3::QtConnectThreeWidget::GetImage(const Square sprite) const noexcept
{
  switch (sprite)
  {
    case Square::empty  : return m_empty;
    case Square::player1: return m_player1;
    case Square::player2: return m_player2;
    case Square::player3: return m_player3;
  }
  assert(!"Should not get here");
  throw std::logic_error("Unknown ribi::con3::QtConnectThreeWidget::GetImage value");
}



