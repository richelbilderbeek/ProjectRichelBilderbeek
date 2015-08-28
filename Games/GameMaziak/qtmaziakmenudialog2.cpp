//---------------------------------------------------------------------------
/*
Maziak, a simple maze game
Copyright (C) 2007-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameMaziak.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtmaziakmenudialog2.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include <boost/scoped_ptr.hpp>

#include <QDesktopWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QMouseEvent>

#include "about.h"
#include "maziakmenudialog.h"
#include "qtaboutdialog.h"
#include "testtimer.h"
#include "qtmaziakcanvas.h"
#include "qtmaziakinstructionsdialog.h"
#include "maziakmaindialog.h"
#include "qtmaziakdisplay.h"
#include "trace.h"
#include "ui_qtmaziakmenudialog2.h"

#pragma GCC diagnostic pop

ribi::maziak::QtMaziakMenuDialog2::QtMaziakMenuDialog2(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtMaziakMenuDialog2),
    m_difficulty(Difficulty::easy)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  //Put the dialog in the screen's center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );
}

ribi::maziak::QtMaziakMenuDialog2::~QtMaziakMenuDialog2() noexcept
{
  delete ui;
}

void ribi::maziak::QtMaziakMenuDialog2::mousePressEvent(QMouseEvent * event)
{
  if (ui->widget_easy->geometry().contains(
    event->x(), event->y()))
  {
    m_difficulty = Difficulty::easy;
    repaint();
    return;
  }
  if (ui->widget_medium->geometry().contains(
    event->x(), event->y()))
  {
    m_difficulty = Difficulty::medium;
    repaint();
    return;
  }
  if (ui->widget_hard->geometry().contains(
    event->x(), event->y()))
  {
    m_difficulty = Difficulty::hard;
    repaint();
    return;
  }
  if (ui->widget_start->geometry().contains(
    event->x(), event->y()))
  {
    OnStart(); return;
  }
  if (ui->widget_instructions->geometry().contains(
    event->x(), event->y()))
  {
    OnInstructions();
    return;
  }
  if (ui->widget_about->geometry().contains(
    event->x(), event->y()))
  {
    OnAbout();
    return;
  }
  if (ui->widget_quit->geometry().contains(
    event->x(), event->y()))
  {
    close();
  }
}

void ribi::maziak::QtMaziakMenuDialog2::keyPressEvent(QKeyEvent * event)
{
  switch (event->key())
  {
    case Qt::Key_Up: case Qt::Key_Left:
    {
      switch (m_difficulty)
      {
        case Difficulty::easy: return;
        case Difficulty::medium: m_difficulty = Difficulty::easy; repaint(); return;
        case Difficulty::hard: m_difficulty = Difficulty::medium; repaint(); return;
        default: assert(!"Should not get here");
      }
    }
    case Qt::Key_Down: case Qt::Key_Right:
    {
      switch (m_difficulty)
      {
        case Difficulty::easy: m_difficulty = Difficulty::medium; repaint(); return;
        case Difficulty::medium: m_difficulty = Difficulty::hard; repaint(); return;
        case Difficulty::hard: return;
        default: assert(!"Should not get here");
      }
    }
    case Qt::Key_S: OnStart(); break;
    case Qt::Key_I: OnInstructions(); break;
    case Qt::Key_A: OnAbout(); break;
    case Qt::Key_Q:
    case Qt::Key_Escape:
      close(); return;
    default:
      break;
  }
}

void ribi::maziak::QtMaziakMenuDialog2::paintEvent(QPaintEvent*)
{
  QPainter painter(this);
  {
    QPixmap background(":/images/GameMaziakBackground.png");
    painter.drawPixmap(rect(),background);
  }

  {
    //Top left
    QPixmap pixmap;
    switch (m_difficulty)
    {
      case Difficulty::easy:
        pixmap = QPixmap(":/images/PlayerWon1.png");
        break;
      case Difficulty::medium:
        pixmap = QPixmap(":/images/PlayerLookDown.png");
        break;
      case Difficulty::hard:
        pixmap = QPixmap(":/images/PlayerScared.png");
        break;
      default:
        assert(!"Should not get here");
    }
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_top_left->geometry(),pixmap);
  }
  {
    //Top right
    QPixmap pixmap;
    switch (m_difficulty)
    {
      case Difficulty::easy:
        pixmap = QPixmap(":/images/Fight2.png");
        break;
      case Difficulty::medium:
        pixmap = QPixmap(":/images/Fight3.png");
        break;
      case Difficulty::hard:
        pixmap = QPixmap(":/images/Fight4.png");
        break;
      default:
        assert(!"Should not get here");
    }
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_top_right->geometry(),pixmap);
  }
  {
    //Easy
    QPixmap pixmap(m_difficulty == Difficulty::easy
      ? ":/images/Easy_selected.png"
      : ":/images/Easy_not_selected.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_easy->geometry(),pixmap);
  }
  {
    //Medium
    QPixmap pixmap(m_difficulty == Difficulty::medium
      ? ":/images/Medium_selected.png"
      : ":/images/Medium_not_selected.png");
    assert(!pixmap.isNull());

    painter.drawPixmap(ui->widget_medium->geometry(),pixmap);
  }
  {
    //Hard
    QPixmap pixmap(m_difficulty == Difficulty::hard
      ? ":/images/Hard_selected.png"
      : ":/images/Hard_not_selected.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_hard->geometry(),pixmap);
  }
  {
    //Start
    QPixmap pixmap(":/images/Start.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_start->geometry(),pixmap);
  }
  {
    //Instructions
    QPixmap pixmap(":/images/Instructions.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_instructions->geometry(),pixmap);
  }
  {
    //About
    QPixmap pixmap(":/images/About.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_about->geometry(),pixmap);
  }
  {
    //Quit
    QPixmap pixmap(":/images/Quit.png");
    assert(!pixmap.isNull());
    painter.drawPixmap(ui->widget_quit->geometry(),pixmap);
  }


}

int ribi::maziak::QtMaziakMenuDialog2::GetMazeSize() const
{
  switch (m_difficulty)
  {
    case Difficulty::easy  : return  99;
    case Difficulty::medium: return 499;
    case Difficulty::hard  : return 999;
  }
  assert(!"Should not get here");
  throw std::logic_error("Unsupported value of mDifficulty");
}

void ribi::maziak::QtMaziakMenuDialog2::OnAbout()
{
  About a = MenuDialog().GetAbout();
  boost::scoped_ptr<QtAboutDialog> d(new QtAboutDialog(a));
  this->ShowChild(d.get());
}

void ribi::maziak::QtMaziakMenuDialog2::OnInstructions()
{
  boost::scoped_ptr<QtMaziakInstructionsDialog> d(new QtMaziakInstructionsDialog);
  this->ShowChild(d.get());
}

void ribi::maziak::QtMaziakMenuDialog2::OnStart()
{
  QtDisplay d;
  MainDialog w(GetMazeSize());
  w.SetDisplay(&d);
  d.DoDisplay(w);
  {
    QRect screen = QApplication::desktop()->screenGeometry();
    d.move( screen.center() - d.rect().center() );
  }
  d.show();
  w.Execute();
}

#ifndef NDEBUG
void ribi::maziak::QtMaziakMenuDialog2::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    MenuDialog();
    QtDisplay();
    QtMaziakInstructionsDialog();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
