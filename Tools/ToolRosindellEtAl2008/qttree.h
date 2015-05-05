//---------------------------------------------------------------------------
/*
RosindellEtAl2008, refactoring an extension of Rosindel at al., 2008 [1]
Copyright (C) 2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolRosindellEtAl2008.htm
//
//Article with original code:
//
// [1] Rosindell, James, Yan Wong, and Rampal S. Etienne.
//     "A coalescence approach to spatial neutral ecology."
//      Ecological Informatics 3.3 (2008): 259-271.
//---------------------------------------------------------------------------
#ifndef QTTREE_H
#define QTTREE_H

#include <QWidget>
#include "tree.h"
#include "rng.h"

namespace Ui {
  class QtTree;
}

class QtTree : public QWidget
{
  Q_OBJECT

public:
  explicit QtTree(QWidget *parent = 0);
  ~QtTree();

  int GetDispersalDistance() const noexcept;
  DispersalKernel GetDispersalKernel() const noexcept;
  int GetLength() const noexcept;
  double GetMinSpeciationRate() const noexcept;
  double GetTolerance() const noexcept;
  Rng GetRng() const noexcept;
  int GetRngSeed() const noexcept;
  Rng::Type GetRngType() const noexcept;
  int GetWidth() const noexcept;

private slots:
  void on_button_start_clicked();

  void on_button_next_clicked();

private:
  Ui::QtTree *ui;

  Rng * m_rng;
  Tree * m_tree;
  std::string m_log;

  void DisplayTree();
};

#endif // QTTREE_H
