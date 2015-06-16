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
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtpvdbaboutdialog.h"

#include <cassert>

#include <QLabel>
#include <QLayout>
#include <QPixmap>

#include "about.h"
#include "pvdbmenudialog.h"
#include "qtarrowitem.h"
#include "qthideandshowdialog.h"
#include "qtkeyboardfriendlygraphicsview.h"
#include "qtquadbezierarrowitem.h"
#include "qtscopeddisable.h"
#pragma GCC diagnostic pop

const boost::shared_ptr<ribi::QtAboutDialog> ribi::pvdb::QtPvdbAboutDialog::Get()
{
  About about = pvdb::MenuDialog().GetAbout();
  about.AddLibrary("QtArrowItem version: " + QtArrowItem::GetVersion());
  about.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  about.AddLibrary("QtKeyboardFriendlyGraphicsView version: " + QtKeyboardFriendlyGraphicsView::GetVersion());
  about.AddLibrary("QtQuadBezierArrowItem version: " + QtQuadBezierArrowItem::GetVersion());
  about.AddLibrary("QtScopedDisable version: " + QtScopedDisable<int>::GetVersion());
  about.AddLibrary("Artwork from LibreOffice");
  const boost::shared_ptr<QtAboutDialog> d(new QtAboutDialog(about));
  assert(d);

  //Add Loom image
  assert(d->layout());
  QLabel * const label = new QLabel(d.get());
  label->setPixmap(QPixmap(":/images/PicLoomAbout.png"));
  d->layout()->addWidget(label);
  return d;
}
