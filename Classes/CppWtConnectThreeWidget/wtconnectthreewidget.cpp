//---------------------------------------------------------------------------
/*
WtConnectThreeWidget, Wt widget for ConnectThree display
Copyright (C) 2010 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppWtConnectThreeWidget.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include "wtconnectthreewidget.h"

#include <cassert>

#include <Wt/WPaintDevice>
#include <Wt/WPainter>
#include <Wt/WTimer>

#include "connectthree.h"
#include "connectthreewidget.h"
#include "connectthreeresources.h"
#include "connectthreemove.h"
#pragma GCC diagnostic pop

///Yes, naming the filename twice feels dumb, but
///I could not find enough documentation about
///how I should use the Wt::WPainter::Image constructor
ribi::con3::WtConnectThreeWidget::WtConnectThreeWidget(
  const boost::shared_ptr<const ConnectThreeResources> resources,
  const std::bitset<3>& is_player_human,
  const int n_cols,
  const int n_rows)
  : m_signal_valid_move{},
    m_widget(new con3::ConnectThreeWidget(is_player_human,n_cols,n_rows)),
    m_players(
      {
        boost::shared_ptr<const Wt::WPainter::Image>(
          new Wt::WPainter::Image(
            resources->GetPlayersFilenames()[0],
            resources->GetPlayersFilenames()[0])),
        boost::shared_ptr<const Wt::WPainter::Image>(
          new Wt::WPainter::Image(
            resources->GetPlayersFilenames()[1],
            resources->GetPlayersFilenames()[1])),
        boost::shared_ptr<const Wt::WPainter::Image>(
          new Wt::WPainter::Image(
            resources->GetPlayersFilenames()[2],
            resources->GetPlayersFilenames()[2])),
      }
    ),
    m_empty(new Wt::WPainter::Image(
      resources->GetEmptyFilename(),
      resources->GetEmptyFilename())),
    m_timer(new Wt::WTimer)
{
  const int sprite_width  = m_empty->width();
  const int sprite_height = m_empty->height();

  this->resize(n_cols * sprite_width,n_rows * sprite_height);
  this->mouseWentDown().connect(this, &ribi::con3::WtConnectThreeWidget::OnClick);
  this->update();
  m_timer->setInterval(100);
  m_timer->timeout().connect(
    boost::bind(
      &ConnectThreeWidget::Tick,
      m_widget.get()));
}

void ribi::con3::WtConnectThreeWidget::DoComputerTurn()
{
  assert(IsComputerTurn());
  const auto move = m_widget->SuggestMove();
  //Check for draw

  if (!move) return;
  assert(m_widget->CanSelect(move->GetX(),move->GetY()));
  m_widget->Select(move->GetX(),move->GetY());
  m_widget->DoMove();
  this->update();
}

ribi::con3::Player ribi::con3::WtConnectThreeWidget::GetActivePlayer() const
{
  return m_widget->GetGame()->GetActivePlayer();
}

const std::bitset<3>& ribi::con3::WtConnectThreeWidget::GetIsPlayerHuman() const
{
  return m_widget->GetIsPlayerHuman();
}

const std::string ribi::con3::WtConnectThreeWidget::GetVersion()
{
  return "2.0";
}

const std::vector<std::string> ribi::con3::WtConnectThreeWidget::GetVersionHistory()
{
  return {
    "2011-01-08: version 1.0: initial version",
    "2011-01-10: version 1.1: added use of ConnectThreeResources",
    "2011-04-22: version 2.0: added Restart, SetIsPlayerHuman methods and a different way of resource acquisition",
    "2014-02-17: version 2.1: put in namespace con3, use of enum classes"
  };
}

ribi::con3::Winner ribi::con3::WtConnectThreeWidget::GetWinner() const
{
  assert(m_widget);
  assert(m_widget->GetGame());
  return m_widget->GetGame()->GetWinner();
}

bool ribi::con3::WtConnectThreeWidget::IsComputerTurn() const
{
  assert(m_widget);
  return m_widget->IsComputerTurn();
}

void ribi::con3::WtConnectThreeWidget::OnClick(const Wt::WMouseEvent& e)
{
  //Disable clicking if it's the AI's turn
  if (IsComputerTurn()) return;

  const int sprite_width  = m_empty->width();
  const int sprite_height = m_empty->height();

  const int mouse_x = e.widget().x;
  const int mouse_y = e.widget().y;
  const int x = mouse_x / sprite_width;
  const int y = mouse_y / sprite_height;
  if (m_widget->GetGame()->CanDoMove(x,y))
  {
    assert(m_widget->CanSelect(x,y));
    m_widget->Select(x,y);
    m_widget->DoMove();
    this->update();
    m_signal_valid_move();
  }

}

void ribi::con3::WtConnectThreeWidget::paintEvent(Wt::WPaintDevice *paintDevice)
{
  Wt::WPainter painter(paintDevice);
  assert(m_widget);
  assert(m_widget->GetGame());
  const int sprite_width  = m_empty->width();
  const int sprite_height = m_empty->height();
  const int n_rows = m_widget->GetGame()->GetRows();
  const int n_cols = m_widget->GetGame()->GetCols();
  for (int y = 0; y!=n_rows; ++y)
  {
    for (int x = 0; x!=n_cols; ++x)
    {
      painter.drawImage(
        x * sprite_width,
        y * sprite_height,
        GetImage(m_widget->GetGame()->GetSquare(x,y)));
    }
  }
}

const Wt::WPainter::Image& ribi::con3::WtConnectThreeWidget::GetImage(const Square sprite) const
{
  switch (sprite)
  {
    case Square::empty: return *m_empty.get();
    case Square::player1: return *m_players[0].get();
    case Square::player2: return *m_players[1].get();
    case Square::player3: return *m_players[2].get();
    default:
      assert(!"Should not get here");
      throw std::logic_error("Unknown ribi::con3::WtConnectThreeWidget::GetImage value");
  }
}

void ribi::con3::WtConnectThreeWidget::Restart()
{
  assert(m_widget);
  m_widget->Restart();
  this->update();
}

void ribi::con3::WtConnectThreeWidget::SetIsPlayerHuman(const std::bitset<3>& is_player_human)
{
  assert(m_widget);
  m_widget->SetIsPlayerHuman(is_player_human);
}



