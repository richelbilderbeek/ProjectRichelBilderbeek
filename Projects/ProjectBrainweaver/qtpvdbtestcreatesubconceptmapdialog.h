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
#ifndef QTPVDBTESTCREATESUBCONCEPTMAPDIALOG_H
#define QTPVDBTESTCREATESUBCONCEPTMAPDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "qtpvdbfwd.h"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPvdbTestCreateSubConceptMapDialog;
}

namespace ribi {

namespace pvdb {

class QtPvdbTestCreateSubConceptMapDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbTestCreateSubConceptMapDialog(QWidget *parent = 0);
  QtPvdbTestCreateSubConceptMapDialog(const QtPvdbTestCreateSubConceptMapDialog&) = delete;
  QtPvdbTestCreateSubConceptMapDialog& operator=(const QtPvdbTestCreateSubConceptMapDialog&) = delete;
  ~QtPvdbTestCreateSubConceptMapDialog() noexcept;

private slots:
  ///The user changes to another concept map
  void OnConceptMapChanged();

  ///The user changes to another sub-concept map
  void OnSubConceptMapChanged();

private:
  Ui::QtPvdbTestCreateSubConceptMapDialog *ui;

  boost::shared_ptr<cmap::QtConceptMap> m_qtconceptmap;
  boost::shared_ptr<cmap::QtConceptMap> m_qtconceptmap_sub;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBTESTCREATESUBCONCEPTMAPDIALOG_H

