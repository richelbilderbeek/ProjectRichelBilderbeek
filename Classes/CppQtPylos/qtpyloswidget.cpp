//---------------------------------------------------------------------------
/*
PylosWidget, widget to display Pylos class
Copyright (C) 2010 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestPylos.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpyloswidget.h"

#include <cassert>
#include <cstdlib>
#include <iostream>

#include <boost/numeric/conversion/cast.hpp>

#include <QMouseEvent>
#include <QPainter>

#include "pylosboard.h"
#include "pylosgame.h"
#include "pylosmove.h"
#include "pylosmustremovestate.h"
#include "pylosplayer.h"
#include "trace.h"

QtPylosWidget::QtPylosWidget() :
    QWidget(0),
    m_select(0,0,0),
    m_sprites(this->width(),this->height(),Pylos::GetRedBlueColors()),
    m_tilt(30.0 * 2.0 * M_PI / 360.0)
{
  //Allows this widget to respond to mouse moving over it
  this->setMouseTracking(true);

  SetSelector(Pylos::Coordinat(0,0,0));

  SaveAllSprites();
  this->setMinimumWidth(64);
  this->setMinimumHeight(64);
}

void QtPylosWidget::DeselectRemove(const Pylos::Coordinat& c)
{
  assert(!m_other_selectors.empty());
  const int sz = boost::numeric_cast<int>(m_other_selectors.size());
  assert(sz == 1 || sz == 2);
  if (sz == 1)
  {
    assert(m_other_selectors[0] == c);
    m_other_selectors.pop_back();
    return;
  }
  assert(sz == 2);
  if (m_other_selectors[0] == c)
  {
    assert(m_other_selectors[1] != c);
    std::swap(m_other_selectors[0],m_other_selectors[1]);
    assert(m_other_selectors.back() == c);
    m_other_selectors.pop_back();
  }
  else
  {
    assert(m_other_selectors[1] == c);
    m_other_selectors.pop_back();
  }
}

void QtPylosWidget::DrawRemove(QPainter& painter, const Pylos::Coordinat& c)
{
  const Pylos::QtSprites::Type sprite =
    ( Get(c) == Pylos::PositionState::player1
     ? Pylos::QtSprites::Type::player1_remove
     : Pylos::QtSprites::Type::player2_remove );

  const std::pair<int,int> p = Transform(c);
  painter.drawPixmap(
    p.first  - (m_sprites.GetMarbleWidth()  / 2),
    p.second - (m_sprites.GetMarbleHeight() / 2),
    m_sprites.Get(sprite));
  /*
  painter.drawPixmap(
      c.GetX() * m_sprites.GetMarbleWidth()  + (c.GetLayer() * (m_sprites.GetMarbleWidth()  / 2)),
      c.GetY() * m_sprites.GetMarbleHeight() + (c.GetLayer() * (m_sprites.GetMarbleHeight() / 2)),
      m_sprites.Get(sprite));
  */
}

void QtPylosWidget::DrawSelect(QPainter& painter)
{
  if (GetWinner() != Pylos::Winner::none) return;
  const Pylos::QtSprites::Type sprite
    = (GetCurrentTurn() == Pylos::Player::player1
    ? Pylos::QtSprites::Type::player1_select
    : Pylos::QtSprites::Type::player2_select);

  const std::pair<int,int> c = Transform(m_select);
  painter.drawPixmap(
    c.first  - (m_sprites.GetMarbleWidth()  / 2),
    c.second - (m_sprites.GetMarbleHeight() / 2),
    m_sprites.Get(sprite));
  /*
  painter.drawPixmap(
    m_select.GetX() * m_sprites.GetMarbleWidth()  + (m_select.GetLayer() * (m_sprites.GetMarbleWidth()  / 2)),
    m_select.GetY() * m_sprites.GetMarbleHeight() + (m_select.GetLayer() * (m_sprites.GetMarbleHeight() / 2)),
    m_sprites.Get(sprite));
  */
}

const std::vector<Pylos::Coordinat> QtPylosWidget::GetCoordinats(
  const int mouse_x, const int mouse_y)
{
  const std::vector<Pylos::Coordinat> v = Pylos::GetAllCoordinats();
  std::vector<double> d; //Distances
  std::transform(v.begin(),v.end(),std::back_inserter(d),
    [this,mouse_x,mouse_y](const Pylos::Coordinat& c)
    {
      //Calculate this Pylos::Coordinat its center on the widget
      const std::pair<int,int> p = Transform(c);

      return GetDistance(
        static_cast<double>(p.first  - mouse_x),
        static_cast<double>(p.second - mouse_y)
        );
    }
  );
  assert(v.size() == d.size());

  std::vector<Pylos::Coordinat> c;

  const std::size_t sz = v.size();
  const double ray = 0.33 * GetDistance(
    static_cast<double>(m_sprites.GetMarbleWidth()),
    static_cast<double>(m_sprites.GetMarbleHeight()) );

  for (std::size_t i=0; i!=sz; ++i)
  {
    if (d[i] < ray) c.push_back(v[i]);
  }
  return c;
}

double QtPylosWidget::GetDistance(const double dx, const double dy)
{
  return std::sqrt( (dx * dx) + (dy * dy) );
}

const std::vector<Pylos::Coordinat>& QtPylosWidget::GetOtherSelectors() const
{
  return m_other_selectors;
}

const std::string QtPylosWidget::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> QtPylosWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-05-28: version 1.0: initial version. Added tilt.");
  return v;
}

bool QtPylosWidget::IsOtherSelector(const Pylos::Coordinat& c) const
{
  return std::find(m_other_selectors.begin(),m_other_selectors.end(),c) != m_other_selectors.end();
}

void QtPylosWidget::MouseLeftClick()
{
  if (!GetMustRemove())
    MouseLeftClickSelect();
  else
    MouseLeftClickRemove();
}

void QtPylosWidget::MouseLeftClickRemove()
{
  //Player tries to select a third marble
  if (m_other_selectors.size() == 2)
  {
    assert(m_select == m_other_selectors[0] || m_select == m_other_selectors[1]);
    DeselectRemove(m_select);
    repaint();
    emit Toggle();
    return;
  }

  //Toggle marbles selected for removal
  {
    bool must_return = false;
    if (std::find(m_other_selectors.begin(),m_other_selectors.end(),m_select) != m_other_selectors.end())
    {
      //Remove c from m_other_selectors,
      //invalidates d
      DeselectRemove(m_select);
      repaint();
      emit Toggle();
      must_return = true;
    }
    if (must_return) return;
  }

  //Player toggles his first marble for removal
  if (m_other_selectors.empty())
  {
    if (CanRemove( std::vector<Pylos::Coordinat>(1,m_select) )) m_other_selectors.push_back(m_select);
    repaint();
    emit Toggle();
    return;
  }

  assert(m_other_selectors.size() == 1);
  //Player clicks a marble and has selected none or one other
  //If the player can remove the selected marble
  //and if he has not selected two marbles
  //for removal already
  if (CanRemove( { m_select,m_other_selectors[0] } ))
  {
    m_other_selectors.push_back(m_select);
    repaint();
    emit Toggle();
  }
}

///MouseLeftClickSelect handles mouse left-clicking
///during select state.
void QtPylosWidget::MouseLeftClickSelect()
{
  if (GetWinner() != Pylos::Winner::none) return;

  //Select marble for movement
  if (m_other_selectors.empty() && CanTransfer(m_select))
  {
    m_other_selectors.push_back(m_select);
    repaint();
    emit Toggle();
    return;
  }
  //Toggle marble selected for movement
  if (!m_other_selectors.empty() && m_select == m_other_selectors[0])
  {
    m_other_selectors.pop_back();
    repaint();
    emit Toggle();
    return;
  }
  //Add marbles
  if (m_other_selectors.empty() && CanSet(m_select))
  {
    Set(m_select);
    m_other_selectors = std::vector<Pylos::Coordinat>();
    repaint();
    emit DoneMove();
    if (GetWinner() != Pylos::Winner::none)
      emit HasWinner();
    return;
  }

    //User might want to move a marble
  if (GetMustRemove() == Pylos::MustRemoveState::no)
  {
    if (!m_other_selectors.empty()
      && CanTransfer(m_other_selectors[0], m_select) )
    {
      Transfer(m_other_selectors[0],m_select);
      emit DoneMove();
      m_other_selectors = std::vector<Pylos::Coordinat>();
      repaint();
    }
    return;
  }
}

void QtPylosWidget::MouseMove(const int mouse_x, const int mouse_y)
{
  if (!GetMustRemove())
    MouseMoveSelect(mouse_x,mouse_y);
  else
    MouseMoveRemoval(mouse_x,mouse_y);
}

void QtPylosWidget::mouseMoveEvent(QMouseEvent * e)
{
  assert(e->type() == QMouseEvent::MouseMove);
  const int mouse_x = e->x();
  const int mouse_y = e->y();
  MouseMove(mouse_x,mouse_y);
}

void QtPylosWidget::mousePressEvent(QMouseEvent* e)
{
  //std::clog << "void QtPylosWidget::mousePressEvent(QMouseEvent* e)\n";
  const int mouse_x = e->x();
  const int mouse_y = e->y();
  MouseMove(mouse_x,mouse_y); //Always first perform a mouse move to set the selector right
  switch (e->button())
  {
    case Qt::LeftButton : MouseLeftClick(); break;
    case Qt::RightButton: MouseRightClick(); break;
    default: break;
  }
}

void QtPylosWidget::MouseMoveRemoval(
  const int mouse_x,
  const int mouse_y)
{

  //Selector must be set to removable marbles
  /*
  //Check lowest Pylos level first, otherwise (0,0,0) cannot be selected when (1,0,0) can be
  for (int layer=0; layer!=4; ++layer)
  {
    const int x = (mouse_x - ((m_sprites.GetMarbleWidth()  / 2) *layer)) / m_sprites.GetMarbleWidth();
    const int y = (mouse_y - ((m_sprites.GetMarbleHeight() / 2) *layer)) / m_sprites.GetMarbleHeight();

    if (!Pylos::Coordinat::IsValid(layer,x,y)) continue;
    Pylos::Coordinat c(layer,x,y);
  */
  const std::vector<Pylos::Coordinat> v = GetCoordinats(mouse_x,mouse_y);
  std::for_each(v.begin(),v.end(),
    [this](const Pylos::Coordinat& c)
    {
      if (
       //player has selected two marbles for removal,
       //only select those marbles
      (m_other_selectors.size() > 0 && IsOtherSelector(c))
       //player has selected one marble for removal,
       //select the marble (possibly below it) to be
       //removed as well
    || (m_other_selectors.size() == 1 && CanRemove( { m_other_selectors[0],c } ))
       //player has selected nothing for removal
    || (m_other_selectors.empty() && CanRemove( std::vector<Pylos::Coordinat>(1,c) ))
      )
      {
        SetSelector(c);
        repaint();
        return;
      }
    }
  );
}

///MouseMoveSelect handles mouse movement
///when player must select either a location to
///place a new marble or to select a marble to move
void QtPylosWidget::MouseMoveSelect(
  const int mouse_x, const int mouse_y)
{
  //Selector must show to either
  //- movable marbles
  //- spots to place a new marble
  //Check lowest Pylos level first, otherwise (0,0,0) cannot be selected when (1,0,0) can be
  /*
  for (int layer=0; layer!=4; ++layer)
  {
    const int x = (mouse_x - ((m_sprites.GetMarbleWidth()  / 2) * layer)) / m_sprites.GetMarbleWidth();
    const int y = (mouse_y - ((m_sprites.GetMarbleHeight() / 2) * layer)) / m_sprites.GetMarbleHeight();

    if (!Pylos::Coordinat::IsValid(layer,x,y)) continue;
    Pylos::Coordinat c(layer,x,y);
  */
  const std::vector<Pylos::Coordinat> v = GetCoordinats(mouse_x,mouse_y);
  std::for_each(v.begin(),v.end(),
    [this](const Pylos::Coordinat& c)
    {
      if (
         //Player selects his/her first position
         ( m_other_selectors.empty()
         //Player can set a new marble there at the current empty position
           && (CanSet(c)
         //Or player can select his/her own marbles for transfer
             || CanTransfer(c) ) )
      || (!m_other_selectors.empty()
           && (IsOtherSelector(c)
             || CanTransfer(m_other_selectors[0],c) ) ) )
      {
        SetSelector(c);
        repaint();
        return;
      }
    }
  );
}

void QtPylosWidget::MouseRightClick()
{
  if (!GetMustRemove()) return;
  //Right mouse button is only used to remove the
  //marbles selected for removal
  //There must be marbles selected
  if (m_other_selectors.empty()) return;
  //Two marbles are selected
  if (CanRemove(m_other_selectors))
  {
    Remove(m_other_selectors);
    emit DoneMove();
    m_other_selectors = std::vector<Pylos::Coordinat>();
    repaint();
  }
}

void QtPylosWidget::paintEvent(QPaintEvent *)
{
  //assert(m_pylos);
  QPainter painter(this);

  painter.drawPixmap(0,0,m_sprites.Get(Pylos::QtSprites::Type::board_bottom));
  //Draw the hole
  for (int y=0; y!=4; ++y)
    for (int x=0; x!=4; ++x)
      painter.drawPixmap(
        x * m_sprites.GetMarbleWidth(),
        y * m_sprites.GetMarbleHeight(),
        m_sprites.Get(Pylos::QtSprites::Type::board_hole));

  for (int layer=0; layer!=4; ++layer)
  {
    const int layer_size = GetLayerSize(layer);
    for (int y=0; y!=layer_size; ++y)
    {
      for (int x=0; x!=layer_size; ++x)
      {
        assert(Pylos::Coordinat::IsValid(layer,x,y));
        const Pylos::Coordinat c(layer,x,y);

        //Draw selector, after sprite is drawn
        if (c == m_select) DrawSelect(painter);

        const Pylos::PositionState state = Get(c);

        Pylos::QtSprites::Type sprite = Pylos::QtSprites::Type::board_hole;
        switch (state)
        {
          case Pylos::PositionState::empty  : continue;
          case Pylos::PositionState::player1: sprite = Pylos::QtSprites::Type::player1; break;
          case Pylos::PositionState::player2: sprite = Pylos::QtSprites::Type::player2; break;
          default: assert(!"Should not get here");
        }
        assert(sprite != Pylos::QtSprites::Type::board_hole);

        const std::pair<int,int> p = Transform(Pylos::Coordinat(layer,x,y));

        painter.drawPixmap(
          p.first  - (m_sprites.GetMarbleWidth()  / 2),
          p.second - (m_sprites.GetMarbleHeight() / 2),
          m_sprites.Get(sprite));
        /*
        painter.drawPixmap(
          x * m_sprites.GetMarbleWidth()  + (layer * (m_sprites.GetMarbleWidth()  / 2)),
          y * m_sprites.GetMarbleHeight() + (layer * (m_sprites.GetMarbleHeight() / 2)),
          m_sprites.Get(sprite));
        */

        //Draw remove
        {
          std::for_each(m_other_selectors.begin(),m_other_selectors.end(),
            [this,c,&painter](const Pylos::Coordinat& d)
            {
              if (d == c) DrawRemove(painter,c);
            }
          );
        }

        //Draw selector, after sprite is drawn
        if (c == m_select) DrawSelect(painter);
      }
    }
  }
}

void QtPylosWidget::resizeEvent(QResizeEvent *)
{
  m_sprites.SetBoardSize(this->width(),this->height());
  repaint();
}

void QtPylosWidget::SaveAllSprites() const
{
  m_sprites.Get(Pylos::QtSprites::Type::player1).save("sprite_player1.png");
  m_sprites.Get(Pylos::QtSprites::Type::player2).save("sprite_player2.png");
  m_sprites.Get(Pylos::QtSprites::Type::player1_select).save("sprite_player1_select.png");
  m_sprites.Get(Pylos::QtSprites::Type::player2_select).save("sprite_player2_select.png");
  m_sprites.Get(Pylos::QtSprites::Type::player1_remove).save("sprite_player1_remove.png");
  m_sprites.Get(Pylos::QtSprites::Type::player2_remove).save("sprite_player2_remove.png");
  m_sprites.Get(Pylos::QtSprites::Type::board_bottom).save("sprite_board_bottom.png");
  m_sprites.Get(Pylos::QtSprites::Type::board_hole).save("sprite_board_hole.png");
}

void QtPylosWidget::SetColorSchemeBlackWhite()
{
  m_sprites.SetColorScheme(Pylos::GetBlackWhiteColors());
  repaint();
}

void QtPylosWidget::SetColorSchemeRedBlue()
{
  m_sprites.SetColorScheme(Pylos::GetRedBlueColors());
  repaint();
}

void QtPylosWidget::SetSelector(const Pylos::Coordinat& c)
{
  m_select = c;
  emit SelectorChanged();
}

void QtPylosWidget::SetTilt(const double tilt)
{
  m_tilt = tilt;
  repaint();
}

const std::pair<int,int> QtPylosWidget::Transform(const Pylos::Coordinat& c) const
{
  const int x_co
    = (m_sprites.GetMarbleWidth() / 2)
    + static_cast<int>(std::sin(m_tilt) * static_cast<double>((m_sprites.GetMarbleWidth()) * (c.GetLayer() + 0)))
    + (c.GetX() * m_sprites.GetMarbleWidth());
  const int y_co
    = (m_sprites.GetMarbleHeight() / 2)
    + static_cast<int>(std::sin(m_tilt) * static_cast<double>((m_sprites.GetMarbleHeight()) * (c.GetLayer() + 0)))
    + (c.GetY() * m_sprites.GetMarbleHeight());
  return std::make_pair(x_co,y_co);
}

