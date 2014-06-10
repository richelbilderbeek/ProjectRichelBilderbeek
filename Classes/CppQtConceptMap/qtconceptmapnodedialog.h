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
#ifndef QTCONCEPTMAPNODEDIALOG_H
#define QTCONCEPTMAPNODEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtNodeDialog; }

namespace ribi {
namespace cmap {

///Displays and modifies a Node
class QtNodeDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtNodeDialog(QWidget *parent = 0);
  QtNodeDialog(const QtNodeDialog&) = delete;
  QtNodeDialog& operator=(const QtNodeDialog&) = delete;
  ~QtNodeDialog();

  void SetNode(const boost::shared_ptr<Node>& node);
  boost::shared_ptr<Node> GetNode() const noexcept { return m_node; }

private slots:
  void on_box_x_valueChanged(double arg1);
  void on_box_y_valueChanged(double arg1);

private:
  Ui::QtNodeDialog *ui;

  ///The Node to work on
  boost::shared_ptr<Node> m_node;

  boost::shared_ptr<QtConceptDialog> m_qtconceptdialog;

  //concept is non-const, as its displayal by this dialog renders it editable
  void OnConceptChanged(Node * const node);
  void OnXchanged(Node * const node);
  void OnYchanged(Node * const node);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPNODEDIALOG_H
