//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2015 The Brainweaver Team

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
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#ifndef QTPVDBOVERVIEWWIDGET_H
#define QTPVDBOVERVIEWWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <QGraphicsView>
#include "pvdbfwd.h"
#pragma GCC diagnostic pop


namespace ribi {

struct QtHideAndShowDialog;

namespace pvdb {

class QtPvdbOverviewWidget : public QGraphicsView
{
  Q_OBJECT

public:

  explicit QtPvdbOverviewWidget(QWidget* parent = 0);
    
public slots:

  void mouseDoubleClickEvent(QMouseEvent *event);

private:

  ///Create all dialogs
  static const std::vector<QtHideAndShowDialog* > GetAllDialogs();

  ///NASTY BUG ALERT: It crashes Wine if m_dialogs is created as
  ///const std::vector<boost::shared_ptr<QtHideAndShowDialog> > m_dialogs;
  ///No idea why...
  const std::vector<QtHideAndShowDialog* > m_dialogs;

};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBOVERVIEWWIDGET_H
