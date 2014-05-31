//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2014 The Brainweaver Team

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
//From http://www.richelbilderbeek.nl/CppQtConceptMap.htm
//---------------------------------------------------------------------------
#ifndef QTCONCEPTMAPEDGEDIALOG_H
#define QTCONCEPTMAPEDGEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtEdgeDialog; }

namespace ribi {
namespace cmap {

///Displays and modifies an Edge
class QtEdgeDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtEdgeDialog(QWidget *parent = 0);
  QtEdgeDialog(const QtEdgeDialog&) = delete;
  QtEdgeDialog& operator=(const QtEdgeDialog&) = delete;
  ~QtEdgeDialog();

  void SetEdge(const boost::shared_ptr<Edge>& edge);
  boost::shared_ptr<Edge> GetEdge() const noexcept { return m_edge; }

private slots:
  void on_box_x_valueChanged(double arg1);
  void on_box_y_valueChanged(double arg1);

private:
  Ui::QtEdgeDialog *ui;

  ///The Edge to work on
  boost::shared_ptr<Edge> m_edge;

  boost::shared_ptr<QtConceptDialog> m_qtconceptdialog;
  boost::shared_ptr<QtNodeDialog> m_qtnodedialog_from;
  boost::shared_ptr<QtNodeDialog> m_qtnodedialog_to;

  //edge is non-const, as its displayal by this dialog renders it editable
  void OnConceptChanged(Edge * const edge);
  void OnXchanged(Edge * const edge);
  void OnYchanged(Edge * const edge);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPEDGEDIALOG_H
