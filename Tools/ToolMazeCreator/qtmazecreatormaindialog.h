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
#ifndef QTMAZECREATORMAINDIALOG_H
#define QTMAZECREATORMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QGraphicsPixmapItem;
struct QGraphicsScene;
struct QTimer;

namespace Ui {
  class QtMazeCreatorMainDialog;
}

namespace ribi {

class QtMazeCreatorMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtMazeCreatorMainDialog(QWidget *parent = 0);
  QtMazeCreatorMainDialog(const QtMazeCreatorMainDialog&) = delete;
  QtMazeCreatorMainDialog& operator=(const QtMazeCreatorMainDialog&) = delete;
  ~QtMazeCreatorMainDialog() noexcept;

  //From http://www.richelbilderbeek.nl/CppCreateMaze.htm
  static const std::vector<std::vector<int> > CreateMaze(const int size);

private:
  Ui::QtMazeCreatorMainDialog *ui;
  boost::shared_ptr<QGraphicsScene> m_scene;
  boost::shared_ptr<QGraphicsPixmapItem> m_background;
  boost::shared_ptr<QTimer> m_timer;

  std::size_t m_maze_sz;
  double m_rotation;


  void resizeEvent(QResizeEvent*);
  void keyPressEvent(QKeyEvent* event);
  void drawMaze();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void onTimer();

};

} //~namespace ribi


#endif // QTMAZECREATORMAINDIALOG_H
