//---------------------------------------------------------------------------
/*
MazeCreator, creates a maze and displays it on screen.
Copyright (C) 2007-2015 Richel Bilderbeek

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
//From hhtp://www.richelbilderbeek.nl/ToolMazeCreator.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtmazecreatormaindialog.h"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include <QDesktopWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>

#include "trace.h"
#include "testtimer.h"
#include "ui_qtmazecreatormaindialog.h"
#pragma GCC diagnostic pop

ribi::QtMazeCreatorMainDialog::QtMazeCreatorMainDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtMazeCreatorMainDialog),
    m_scene(new QGraphicsScene),
    m_background(new QGraphicsPixmapItem),
    m_timer(new QTimer),
    m_maze_sz(7),
    m_rotation(0.0)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  ui->graphicsView->setScene(m_scene.get());
  m_scene->addItem(m_background.get());

  this->drawMaze();

  //Set all connections
  QObject::connect(m_timer.get(),&QTimer::timeout,
    this,&ribi::QtMazeCreatorMainDialog::onTimer
  );

  //Set the rotation timer to work
  m_timer->start(50);

  //Put the dialog to its proper size and spot
  this->setGeometry(0,0,
    static_cast<int>(640),
    static_cast<int>(640));
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );
}

ribi::QtMazeCreatorMainDialog::~QtMazeCreatorMainDialog() noexcept
{
  delete ui;
}

//Sets the scale of the maze
void ribi::QtMazeCreatorMainDialog::resizeEvent(QResizeEvent*)
{
  const double scale
    = 0.9 * std::min(ui->graphicsView->width(),ui->graphicsView->height())
    / (static_cast<double>(this->m_maze_sz) * std::sqrt(2.0));
  m_background->setScale(scale);
}

void ribi::QtMazeCreatorMainDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->type() == QEvent::KeyPress)
  {
    //std::clog << "Key pressed\n";
    switch (event->key())
    {
      case Qt::Key_Plus:
          //std::clog << "Key plus pressed\n";
          m_maze_sz+=4;
          drawMaze();
          resizeEvent(0);
        break;
      case Qt::Key_Minus:
          //std::clog << "Key minus pressed\n";
          if (m_maze_sz == 7) return;
          m_maze_sz-=4;
          drawMaze();
          resizeEvent(0);
        break;
    }
  }
}

void ribi::QtMazeCreatorMainDialog::drawMaze()
{
  const int size = static_cast<int>(m_maze_sz);
  //Prepare a pixmap of right size
  //and set the rotation origin
  {
    QPixmap pixmap(size,size);
    m_background->setPixmap(pixmap);
    m_background->setTransformOriginPoint(
      static_cast<double>(size) / 2.0,
      static_cast<double>(size) / 2.0);
  }

  const std::vector<std::vector<int> > maze = CreateMaze(size);
  assert(maze.size() == m_maze_sz);
  assert(maze[0].size() == m_maze_sz);

  QImage i = m_background->pixmap().toImage();

  for (int y=0; y!=size; ++y)
  {
    for (int x=0; x!=size; ++x)
    {
      switch(maze[x][y])
      {
        case 0: //Road
          i.setPixel(QPoint(x,y),QColor(255,255,255).rgb());
          break;
        case 1: //Wall
          i.setPixel(QPoint(x,y),QColor(0,0,0).rgb());
          break;
        case 2: //Unexplorer
          i.setPixel(QPoint(x,y),QColor(255,0,0).rgb());
          break;
        default:
          std::cerr << maze[x][y] << '\n';
          assert(!"Should not get here");
          break;
      }
    }
  }
  m_background->setPixmap(m_background->pixmap().fromImage(i));
}

void ribi::QtMazeCreatorMainDialog::onTimer()
{
  m_rotation+=1.0;
  m_background->setRotation(m_rotation);
}

//Creates a maze
// 0 : path
// 1 : wall
//From http://www.richelbilderbeek.nl/CppCreateMaze.htm
const std::vector<std::vector<int> > ribi::QtMazeCreatorMainDialog::CreateMaze(const int sz)
{
  //Assume correct size dimensions
  assert( sz > 4 && sz % 4 == 3
    && "Size must be 3 + (n * 4) for n > 0");

  //Start with a wall-only maze
  std::vector<std::vector<int> > maze(sz, std::vector<int>(sz,1));

  //Prepare maze, remove paths
  // XXXXXXX    1111111
  // X X X X    1212121
  // XXXXXXX    1111111
  // X XOX X -> 1210121
  // XXXXXXX    1111111
  // X X X X    1212121
  // XXXXXXX    1111111

  //Draw open spaces
  for (int y=1; y<sz; y+=2)
  {
    for (int x=1; x<sz; x+=2)
    {
      maze[y][x] = 2; //2: unexplored
    }
  }

  const int mid = sz/2;

  maze[mid][mid] = 0;

  std::vector<std::pair<int,int> > v;
  v.push_back(std::make_pair(mid,mid));
  while (!v.empty())
  {
    //Set a random explorer square at the back
    std::swap(v.back(),v[ std::rand() % static_cast<int>(v.size())]);
    //Check possible adjacent squares
    const int x = v.back().first;
    const int y = v.back().second;
    std::vector<std::pair<int,int> > next;
    if (x > 0 + 2 && maze[y][x-2] == 2) next.push_back(std::make_pair(x-2,y));
    if (y > 0 + 2 && maze[y-2][x] == 2) next.push_back(std::make_pair(x,y-2));
    if (x < sz - 2 && maze[y][x+2] == 2) next.push_back(std::make_pair(x+2,y));
    if (y < sz - 2 && maze[y+2][x] == 2) next.push_back(std::make_pair(x,y+2));
    //Dead end?
    if (next.empty())
    {
      v.pop_back();
      continue;
    }
    //Select a random next adjacent square
    const int nextIndex = (std::rand() >> 4) % static_cast<int>(next.size());
    const int nextX = next[nextIndex].first;
    const int nextY = next[nextIndex].second;
    //Clear next square
    maze[nextY][nextX] = 0;
    //Clear path towards next square
    maze[(y + nextY)/2][(x + nextX)/2] = 0;
    //Add next square to stack
    v.push_back(std::make_pair(nextX,nextY));
  }
  return maze;
}

#ifndef NDEBUG
void ribi::QtMazeCreatorMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
