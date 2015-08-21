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
#ifndef QTPVDBRATECONCEPTMAPDIALOG_H
#define QTPVDBRATECONCEPTMAPDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtpvdbfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtPvdbRateConceptMapDialog; }

namespace ribi {
namespace pvdb {

class QtPvdbRateConceptMapDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  using ConceptMap = cmap::QtConceptMap;
  explicit QtPvdbRateConceptMapDialog(
    boost::shared_ptr<pvdb::File> file,
    QWidget* parent = 0);
  QtPvdbRateConceptMapDialog(const QtPvdbRateConceptMapDialog&) = delete;
  QtPvdbRateConceptMapDialog& operator=(const QtPvdbRateConceptMapDialog&) = delete;
  ~QtPvdbRateConceptMapDialog() noexcept;

  cmap::QtConceptMap * GetWidget();

  ///Respond to key press
  void keyPressEvent(QKeyEvent *);

  void Save();
  void Save(const std::string& filename);

private slots:
  void on_button_next_clicked();

  void on_button_save_clicked();

private:
  Ui::QtPvdbRateConceptMapDialog *ui;
  boost::shared_ptr<pvdb::File> m_file;
  ConceptMap * const m_concept_map;

  ///The widget requested for a rating of the already supplied sub concept map,
  ///with the focal concept item as the central node
  void OnRequestRateConceptDialog(const boost::shared_ptr<ribi::cmap::ConceptMap> sub_concept_map);

  static void Test() noexcept;
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTPVDBRATECONCEPTMAPDIALOG_H
