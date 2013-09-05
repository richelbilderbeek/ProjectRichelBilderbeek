#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconnectthreewidget.h"
#pragma GCC diagnostic pop

#include <QMouseEvent>
#include <QPainter>

#include "connectthree.h"
#include "connectthreeresources.h"
#include "connectthreewidget.h"
#include "qtconnectthreeresources.h"

const int ribi::QtConnectThreeWidget::m_sprite_width  = 50;
const int ribi::QtConnectThreeWidget::m_sprite_height = 50;

ribi::QtConnectThreeWidget::QtConnectThreeWidget(
  const boost::shared_ptr<const ConnectThreeResources> resources,
  QWidget *parent,
  const std::bitset<3>& is_player_human,
  const int n_cols,
  const int n_rows)
  : QWidget(parent),
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

void ribi::QtConnectThreeWidget::DoComputerTurn()
{
  assert(IsComputerTurn());
  const ConnectThree::Move move = m_widget->SuggestMove();
  m_widget->DoMove(move.get<0>(),move.get<1>());
  this->update();
}

int ribi::QtConnectThreeWidget::GetActivePlayer() const
{
  return m_widget->GetGame()->GetActivePlayer();
}

const std::string ribi::QtConnectThreeWidget::GetVersion()
{
  return "2.0";
}

const std::vector<std::string> ribi::QtConnectThreeWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-01-10: version 1.0: initial version");
  v.push_back("2011-04-20: version 2.0: Moved logic to ConnectThreeWidget");
  return v;
}

int ribi::QtConnectThreeWidget::GetWinner() const
{
  return m_widget->GetGame()->GetWinner();
}

bool ribi::QtConnectThreeWidget::IsComputerTurn() const
{
  return m_widget->IsComputerTurn();
}

void ribi::QtConnectThreeWidget::mousePressEvent(QMouseEvent * e)
{
  //Disable clicking if it's the AI's turn
  if (IsComputerTurn()) return;

  const int mouse_x = e->x();
  const int mouse_y = e->y();
  const int x = mouse_x / m_sprite_width;
  const int y = mouse_y / m_sprite_height;
  if (m_widget->GetGame()->CanDoMove(x,y))
  {
    m_widget->DoMove(x,y);
    this->update();
    m_signal_valid_move();
  }
}

void ribi::QtConnectThreeWidget::paintEvent(QPaintEvent *)
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
        GetImage(m_widget->GetGame()->GetSquare(x,y)));
    }
  }
}

const QImage& ribi::QtConnectThreeWidget::GetImage(const int sprite) const
{
  switch (sprite)
  {
    case ConnectThree::no_player: return m_empty;
    case ConnectThree::player1  : return m_player1;
    case ConnectThree::player2  : return m_player2;
    case ConnectThree::player3  : return m_player3;
  }
  assert(!"Should not get here");
  throw std::logic_error("Unknown ribi::QtConnectThreeWidget::GetImage value");
}



