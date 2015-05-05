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
#include "qttree.h"

#include <cassert>
#include <sstream>

#include <QDesktopWidget>

#include "simulation.h"
#include "ui_qttree.h"

QtTree::QtTree(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtTree),
  m_rng{nullptr},
  m_tree{nullptr}
{
  #ifndef NDEBUG
  Rng::Test();
  Tree::Test();
  Simulation::Test();
  #endif

  ui->setupUi(this);
  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->move( screen.center() - this->rect().center() );
  }
}

QtTree::~QtTree()
{
  delete ui;
}

void QtTree::DisplayTree()
{
  if (!m_tree) return;
  std::stringstream s;
  m_tree->DisplayActive(s);
  m_log += s.str() + "\n";
  ui->text->setPlainText(m_log.c_str());
}

int QtTree::GetDispersalDistance() const noexcept
{
  return ui->box_dispersal_distance->value();
}

DispersalKernel QtTree::GetDispersalKernel() const noexcept
{
  if (ui->box_dispersal_type->currentText() == "Square") return DispersalKernel::square;
  if (ui->box_dispersal_type->currentText() == "Normal") return DispersalKernel::normal;
  assert(!"Should not get here");
  throw std::logic_error("QtTree::GetDispersalKernel: unknown text"); //Crashes the program on purpose
}

int QtTree::GetLength() const noexcept
{
  return ui->box_height->value();
}

double QtTree::GetMinSpeciationRate() const noexcept
{
  return ui->box_min_speciation_rate->value();
}

double QtTree::GetTolerance() const noexcept
{
  return ui->box_tolerance->value();
}

Rng QtTree::GetRng() const noexcept
{
  return Rng(GetRngSeed(),GetRngType());
}

int QtTree::GetRngSeed() const noexcept
{
  return ui->box_rng_seed->value();
}

Rng::Type QtTree::GetRngType() const noexcept
{
  if (ui->box_rng_type->currentText() == "Bilderbeek") { return Rng::Type::bilderbeek;  }
  if (ui->box_rng_type->currentText() == "Rosindell" ) { return Rng::Type::rosindell;  }
  assert(!"Should not get here");
  throw std::logic_error("QtTree::GetRngType: unknown text"); //Crashes the program on purpose
}

int QtTree::GetWidth() const noexcept
{
  return ui->box_width->value();
}

void QtTree::on_button_start_clicked()
{
  delete m_rng;
  m_rng = new Rng(GetRngSeed(),GetRngType());

  delete m_tree;
  m_tree = new Tree(
    *m_rng,
    GetWidth(),
    GetLength(),
    GetMinSpeciationRate(),
    GetDispersalDistance(),
    GetTolerance(),
    GetDispersalKernel()
  );
  m_log.clear();

  DisplayTree();
}

void QtTree::on_button_next_clicked()
{
  if (!m_tree) return;
  m_tree->Update();
  DisplayTree();
}
