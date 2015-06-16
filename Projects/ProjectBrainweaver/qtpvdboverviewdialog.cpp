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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtpvdboverviewdialog.h"

#include <QKeyEvent>
#include <QVBoxLayout>

#include "qtpvdboverviewwidget.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::pvdb::QtPvdbOverviewDialog::QtPvdbOverviewDialog(QWidget* parent)
  : QtHideAndShowDialog(parent)
{
  
  QLayout * const layout = new QVBoxLayout(this);
  this->setLayout(layout);
  QtPvdbOverviewWidget * const widget = new QtPvdbOverviewWidget;
  layout->addWidget(widget);
}

void ribi::pvdb::QtPvdbOverviewDialog::keyPressEvent(QKeyEvent* e)
{
  assert(e);
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  QDialog::keyPressEvent(e);
}
